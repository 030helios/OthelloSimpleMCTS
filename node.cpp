#include "func.h"
#include "node.h"
#include <math.h>
#include <algorithm>
using namespace std;

Node::Node() {}
Node::Node(const Node &t)
{
    col = t.col;
    board = t.board;
}
//init as pass
Node::Node(array<int8_t, BoardSize> &bd, int8_t co)
{
    col = co;
    board = bd;
}
//init with move to generate child node
Node::Node(array<int8_t, BoardSize> &bd, int8_t &x, int8_t &y, int8_t co)
{
    board = bd;
    playMoveAssumeLegal(board, co, x, y);
    col = -co;
}
//returns child that matches the input
Node *Node::playermove(array<int8_t, BoardSize> &target)
{
    children.push_back(*this);
    while (children[0].board != target)
        children.pop_front();
    children.resize(1);
    return &children[0];
}
//return UCB
float Node::UCB(int &N, int8_t parentColor)
{
    std::lock_guard<std::mutex> lock(mtx);
    if (totalgames)
    {
        if (gameover != -2)
            return 1000 * parentColor * gameover;
        float a = global_C * sqrt((log(N)) / ((float)totalgames));
        a += ((float)(totalgames - wins) / (totalgames));
        return a;
    }
    return 0;
}
//removes data without removing the structure
void Node::clean()
{
    wins = 0;
    totalgames = 0;
    int childsize = children.size();
    for (auto child = children.begin(); child != children.cend(); child++)
        child->clean();
}
//discover moves and store in haschild, pass if needed
void Node::getmoves()
{
    legalMoves(board, col, moves, haschild);
    if (!haschild)
    {
        haschild = -1;
        if (!won(board)[1])
            children.emplace_back(board, -col);
    }
    else
        random_shuffle(moves.begin(), moves.begin() + haschild - 1);
}
int8_t Node::explore()
{
    if (gameover != -2)
        return gameover;
    Node *child = nullptr;
    {
        std::lock_guard<std::mutex> lock(child_mtx);
        if (haschild == 0)
            getmoves();
        if (haschild > 0)
        {
            haschild--;
            children.emplace_back(board, moves[haschild].first, moves[haschild].second, col);
            child = &children.back();
            if (haschild == 0)
                haschild--;
        }
        else
            child = select();
    }
    if (child == nullptr)
    {
        std::lock_guard<std::mutex> lock(mtx);
        gameover = won(board)[0];
        return gameover;
    }
    else
    {
        int8_t outcome = child->explore();
        std::lock_guard<std::mutex> lock(mtx);
        totalgames++;
        wins += (outcome == col);
        return outcome;
    }
}
//return greatest UCB child number
Node *Node::select()
{
    float ucbmax = -INFINITY;
    int total;
    {
        std::lock_guard<std::mutex> lock(mtx);
        total = totalgames;
    }
    Node *best = nullptr;
    for (auto child = children.begin(); child != children.cend(); child++)
    {
        float ucb = child->UCB(total, col);
        if (ucb > ucbmax || (ucb == ucbmax && rand() % 2))
        {
            ucbmax = ucb;
            best = &*child;
        }
    }
    if (best != nullptr)
    {
        std::lock_guard<std::mutex> lock(mtx);
        std::lock_guard<std::mutex> lock1(best->mtx);
        if (best->gameover != -2)
            gameover = best->gameover;
    }
    return best;
}
//return best board
Node *Node::getbest()
{
    int imax = 0;
    for (int i = 0; i < children.size(); i++)
        if (children[i].totalgames > children[imax].totalgames || children[i].gameover == col)
            imax = i;
    for (int i = 0; i < imax; i++)
        children.pop_front();
    children.resize(1);
    return &children[0];
}