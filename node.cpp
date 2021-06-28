#include "func.h"
#include "node.h"
#include <math.h>
#include <iostream>
#include <algorithm>
using namespace std;

Node::Node() {}
Node::Node(const Node &t)
{
    col = t.col;
    board = t.board;
}
//init as pass
Node::Node(array<int8_t, 64> &bd, int8_t co)
{
    col = co;
    board = bd;
}
//init with move to generate child node
Node::Node(array<int8_t, 64> &bd, int8_t &x, int8_t &y, int8_t co)
{
    board = bd;
    playMoveAssumeLegal(board, co, x, y);
    col = -co;
}
//returns child that matches the input
Node *Node::playermove(array<int8_t, 64> &target)
{
    if (haschild == 0)
        return this;
    while (children[0].board != target)
        children.pop_front();
    children.resize(1);
    return &children[0];
}
//return UCB
float Node::UCB(int &N)
{
    if (gameover == 1 || gameover == -1)
        return -INFINITY * col * gameover;
    if (totalgames)
    {
        float a = global_C * sqrt((log(N)) / ((float)totalgames));
        a += ((float)(totalgames - wins) / (totalgames));
        return a;
    }
    return 100000;
}
//removes data without removing the structure
void Node::clean()
{
    wins = 0;
    totalgames = 0;
    int childsize = children.size();
    for (int i = 0; i < childsize; i++)
        children[i].clean();
}
//discover moves and store in haschild, pass if needed
void Node::getmoves()
{
    legalMoves(board, col, moves, haschild);
    if (!haschild)
    {
        haschild = -1;
        if (!won(board)[1])
        {
            Node kid(board, -col);
            children.push_back(kid);
        }
    }
    else
        random_shuffle(moves.begin(), moves.begin() + haschild - 1);
}
int8_t Node::explore()
{
    int8_t index;
    {
        std::lock_guard<std::mutex> lock(child_mtx);
        if (haschild == 0)
            getmoves();
        if (haschild > 0)
        {
            haschild--;
            index = children.size();
            Node kid(board, moves[haschild].first, moves[haschild].second, col);
            children.push_back(kid);
            if (haschild == 0)
                haschild--;
        }
        else
        {
            if (gameover != -2)
                return gameover;
            index = select();
        }
    }
    if (index == -1)
    {
        std::lock_guard<std::mutex> lock(mtx);
        gameover = won(board)[0];
        return gameover;
    }
    else
    {
        int8_t outcome = children[index].explore();
        std::lock_guard<std::mutex> lock(mtx);
        totalgames++;
        wins += (outcome == col);
        return outcome;
    }
}
//return greatest UCB child number
int8_t Node::select()
{
    float ucbmax = 0;
    float ucb;
    int8_t childsize = children.size();
    int8_t imax = childsize - 1;
    for (int8_t i = 0; i < childsize; i++)
    {
        ucb = children[i].UCB(totalgames);
        if (ucb > ucbmax)
        {
            ucbmax = ucb;
            imax = i;
        }
        else if (ucb == ucbmax && rand() % 2)
        {
            ucbmax = ucb;
            imax = i;
        }
    }
    if (ucbmax == INFINITY)
        gameover = col;
    else if (ucbmax == -INFINITY)
        gameover = -col;
    return imax;
}
//return best board
Node *Node::getbest()
{
    int imax = 0;
    for (int i = 0; i < children.size(); i++)
        if (children[i].totalgames > children[imax].totalgames)
            imax = i;
    for (int i = 0; i < imax; i++)
        children.pop_front();
    children.resize(1);
    return &children[0];
}