#include "func.h"
#include "node.h"
using namespace std;

Node::Node() {}
Node::Node(const Node &t)
{
    col = t.col;
    RdId = t.RdId;
    board = t.board;
}
//init as pass
Node::Node(array<int8_t, BoardSize> &bd, int8_t co)
{
    col = co;
    RdId = rand() % BoardSize;
    board = bd;
}
//return UCB
float Node::UCB(int &N, int8_t parentColor)
{
    lock_guard<mutex> lock(mtx);
    if (!totalgames)
        return 512;
    if (gameover != -2)
        return 1024 * parentColor * gameover;
    float a = sqrt(2 * log(N) / (float)totalgames);
    a += ((float)(totalgames - wins) / (totalgames));
    return a;
}
//removes data without removing the structure
void Node::clean()
{
    wins = 0;
    totalgames = 0;
    for (auto &child : children)
        child.clean();
}
int8_t Node::explore()
{
    Node *child;
    {
        lock_guard<mutex> lock(child_mtx);
        {
            lock_guard<mutex> lock(mtx);
            if (gameover != -2)
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
                    return gameover;
                }
        }
        else
            child = select();
    }
    int8_t outcome = child->explore();
    lock_guard<mutex> lock(mtx);
    totalgames++;
    wins += (outcome == col);
    return outcome;
}
//return greatest UCB child number
Node *Node::select()
{
    float ucbmax = -INFINITY;
    Node *best = nullptr;
    int total;
    {
        lock_guard<mutex> lock(mtx);
        total = totalgames;
    }
    for (auto &child : children)
    {
        float ucb = child.UCB(total, col);
        if (ucb > ucbmax)
        {
            ucbmax = ucb;
            best = &child;
        }
        else if (ucb == ucbmax && rand() % 2)
        {
            ucbmax = ucb;
            best = &child;
        }
    }
    if (best)
    {
        lock_guard<mutex> lock(mtx);
        lock_guard<mutex> lock1(best->mtx);
        gameover = best->gameover;
    }
    else
        best = &children.front();
    return best;
}
//return best board
Node *Node::getbest()
{
    int imax = 0;
    for (int i = 0; i < children.size(); i++)
    {
        if (children[i].gameover == col)
        {
            imax = i;
            break;
        }
        if (children[i].totalgames > children[imax].totalgames)
            imax = i;
    }
    for (int i = 0; i < imax; i++)
        children.pop_front();
    children.resize(1);
    return &children.front();
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