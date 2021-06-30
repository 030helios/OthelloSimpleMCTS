#include "func.h"
#include "node.h"
#include <iostream>
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
    std::lock_guard<std::mutex> lock(mtx);
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
    int childsize = children.size();
    for (auto &child : children)
        child.clean();
}
int8_t Node::explore()
{
    if (gameover != -2)
        return gameover;
    Node *child = nullptr;
    {
        std::lock_guard<std::mutex> lock(child_mtx);
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
                    children.pop_back();
                    std::lock_guard<std::mutex> lock1(mtx);
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
    std::lock_guard<std::mutex> lock(mtx);
    if (child->gameover == col || moveIndex < 0)
        gameover = child->gameover;
    totalgames++;
    wins += (outcome == col);
    return outcome;
}
//return greatest UCB child number
Node *Node::select()
{
    float ucbmax = -INFINITY;
    int total = totalgames;
    Node *best = nullptr;
    for (auto &child : children)
    {
        float ucb = child.UCB(total, col);
        if (ucb > ucbmax || (ucb == ucbmax && rand() % 2))
        {
            ucbmax = ucb;
            best = &child;
        }
    }
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
    return &children[0];
}
//returns child that matches the input
Node *Node::playermove(array<int8_t, BoardSize> &target)
{
    children.push_back(*this);
    while (children.size())
        if (children[0].board != target)
            children.pop_front();
        else
            break;
    if (children.size() == 0)
    {
        printboard(board, "ErrorBoard");
        printboard(target, "ErrorTarget");
        int junk;
        cin >> junk;
    }
    children.resize(1);
    return &children[0];
}