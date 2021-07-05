#include "func.h"
#include "node.h"
using namespace std;

Node::Node() {}
Node::Node(array<int8_t, BoardSize> &bd, int8_t co) : col(co), RdId(rand() % BoardSize), board(bd) {}
//removes data without removing the structure
void Node::clean()
{
    score = 0;
    totalgames = 0;
    for (auto &child : children)
        child.clean();
}
//initializes new child if possible
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
//returns child with greatest UCB
Node *Node::select()
{
    float ucbmax = -INFINITY;
    Node *best = nullptr;
    for (auto &child : children)
    {
        lock_guard<mutex> lock(child.mtx);
        if (child.totalgames == 0)
            return &child;
        float ucb = child.UCB(totalgames, col);
        if (ucb > ucbmax)
        {
            ucbmax = ucb;
            best = &child;
            gameover = best->gameover;
        }
    }
    return best;
}
//Heat determines whether to allocate new child or not
int Node::explore(int8_t heat)
{
    Node *child = nullptr;
    {
        lock_guard<mutex> lock(mtx);
        totalgames++;
        if (gameover != -2 && gameover != 0)
            return gameover;
        if (heat == 0)
        {
            score = playout(board, col);
            return score;
        }
        if (moveIndex >= 0)
            child = getNewChild();
        if (child == nullptr)
            child = select();
        else
            heat--;
        if (child == nullptr)
        { //won
            gameover = 0;
            for (auto stone : board)
                gameover += stone;
            gameover = (gameover > 0) - (gameover < 0);
            return gameover;
        }
    }
    int outcome = child->explore(heat);

    lock_guard<mutex> lock(mtx);
    score += outcome;
    if (gameover != -2 && gameover != 0)
    {
        outcome = totalgames * gameover - score;
        score = gameover * totalgames;
    }
    return outcome;
}
//returns the most visited child node
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