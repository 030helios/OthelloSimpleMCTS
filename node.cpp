#include "func.h"
#include "node.h"
using namespace std;

Node::Node()
{
    sem_init(&sem, 0, 1);
}
Node::Node(const Node &t)
{
    col = t.col;
    RdId = t.RdId;
    board = t.board;
    sem_init(&sem, 0, 1);
}
Node::Node(array<int8_t, BoardSize> &bd, int8_t co)
{
    col = co;
    RdId = rand() % BoardSize;
    board = bd;
    sem_init(&sem, 0, 1);
}
//return UCB
float Node::UCB(int &N, int8_t parentColor)
{
    if (gameover != -2)
        if (gameover != 0)
            return 1024 * parentColor * gameover;
        else if (totalgames)
            return 0.5 + sqrt(2 * log(N) / (float)totalgames);
        else
            return 511;
    if (!totalgames)
        return 512;
    float a = sqrt(2 * log(N) / (float)totalgames);
    a += 0.5 + (float)(points) / (parentColor * 2 * totalgames);
    return a;
}
//removes data without removing the structure
void Node::clean()
{
    points = 0;
    totalgames = 0;
    for (auto &child : children)
        child.clean();
}
int8_t Node::explore()
{
    Node *child;
    {
        sem_wait(&sem);
        totalgames++;
        if (gameover != -2)
        {
            sem_post(&sem);
            return gameover;
        }
        if (moveIndex >= 0)
        {
            children.emplace_back(board, -col);
            child = &children.back();
            if (!newMove(children.back().board, col, RdId, moveIndex)) //searched
                if (children.size() > 1)
                { // has children
                    children.pop_back();
                    child = select();
                }
                else if (!hasMove(board, -col))
                { //won
                    gameover = 0;
                    for (auto stone : board)
                        gameover += stone;
                    gameover = (gameover > 0) - (gameover < 0);
                    sem_post(&sem);
                    return gameover;
                }
        }
        else
            child = select();
        sem_post(&sem);
    }
    int8_t outcome = child->explore();
    sem_wait(&sem);
    points += outcome;
    sem_post(&sem);
    return outcome;
}
//return greatest UCB child number
Node *Node::select()
{
    float ucbmax = -INFINITY;
    Node *best = nullptr;
    for (auto &child : children)
    {
        sem_wait(&child.sem);
        float ucb = child.UCB(totalgames, col);
        if (ucb > ucbmax)
        {
            ucbmax = ucb;
            best = &child;
            gameover = best->gameover;
        }
        else if (ucb == ucbmax)
            if (rand() % 2)
            {
                ucbmax = ucb;
                best = &child;
            }
        sem_post(&child.sem);
    }
    return best;
}
//return best board
Node *Node::getbest()
{
    Node *best = select();
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