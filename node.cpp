#include "func.h"
#include "node.h"
using namespace std;

Node::Node()
{
    sem_init(&sem, 0, 1);
}
Node::Node(const Node &t) : col(t.col), RdId(t.RdId), board(t.board)
{
    sem_init(&sem, 0, 1);
}
Node::Node(array<int8_t, BoardSize> &bd, int8_t co) : col(co), RdId(rand() % BoardSize), board(bd)
{
    sem_init(&sem, 0, 1);
}
//return UCB
float Node::UCB(int &N, int8_t parentColor)
{
    if (gameover != -2)
        if (gameover != 0)
            return N * parentColor * gameover;
        else
            return 0.5 + sqrt(2 * log(N) / (float)totalgames);
    float a = sqrt(2 * log(N) / (float)totalgames);
    a += 0.5 + (float)(score) / (parentColor * 2 * totalgames);
    return a;
}
//removes data without removing the structure
void Node::clean()
{
    score = 0;
    totalgames = 0;
    for (auto &child : children)
        child.clean();
}
Node *Node::getNewChild()
{
    children.emplace_back(board, -col);
    if (newMove(children.back().board, col, RdId, moveIndex))
        return &children.back();
    else if (children.size() > 1) // has children
        children.pop_back();
    else if (!hasMove(board, -col)) //won
        children.pop_back();
    else //pass
        return &children.back();
    return nullptr;
}
//Heat determines whether to allocate new child or not
int Node::explore(int8_t heat)
{
    Node *child = nullptr;
    sem_wait(&sem);
    totalgames++;
    if (gameover != -2 && gameover != 0)
    {
        sem_post(&sem);
        return gameover;
    }
    if (heat == 0)
    {
        int outcome = playout(board, col);
        score += outcome;
        sem_post(&sem);
        return outcome;
    }
    if (moveIndex >= 0)
    {
        heat -= 1;
        child = getNewChild();
    }
    if (child == nullptr)
        child = select();
    if (child == nullptr)
    { //won
        gameover = 0;
        for (auto stone : board)
            gameover += stone;
        gameover = (gameover > 0) - (gameover < 0);
        sem_post(&sem);
        return gameover;
    }
    sem_post(&sem);

    int outcome = child->explore(heat);
    sem_wait(&sem);
    score += outcome;
    if (gameover != -2 && gameover != 0)
    {
        outcome = totalgames * gameover - score;
        score = gameover * totalgames;
    }
    sem_post(&sem);
    return outcome;
}
Node *Node::select()
{
    float ucbmax = -INFINITY;
    Node *best = nullptr;
    for (auto &child : children)
    {
        sem_wait(&child.sem);
        if (child.totalgames == 0)
        {
            sem_post(&child.sem);
            return &child;
        }
        float ucb = child.UCB(totalgames, col);
        if (ucb > ucbmax)
        {
            ucbmax = ucb;
            best = &child;
            gameover = best->gameover;
        }
        sem_post(&child.sem);
    }
    return best;
}
//return best board
Node *Node::getbest()
{
    Node *best = &children.front();
    for (auto &child : children)
        if (child.totalgames > best->totalgames)
            best = &child;
    for (auto &child : children)
        if (child.gameover == col)
            best = &child;
    while (&children.front() != best)
        children.pop_front();
    children.resize(1);
    return best;
}
//returns child that matches the input
Node *Node::playermove(array<int8_t, BoardSize> &target)
{
    if (target != board)
        while (children.size())
            if (children.front().board != target)
                children.pop_front();
            else
                break;
    if (children[0].board == target)
    {
        children.resize(1);
        return &children[0];
    }
    return this;
}