#include "func.h"
#include "node.h"
#include <algorithm>
#include <mutex>
#include <math.h>
#include <vector>
#include <iostream>
using namespace std;

Node::Node() {}
Node::Node(const Node &t)
{
    col = t.col;
    board = t.board;
}
//init as pass
Node::Node(vector<vector<int>> &bd, int co)
{
    col = co;
    board = bd;
}
//init with move to generate child node
Node::Node(vector<vector<int>> &bd, int &x, int &y, int co)
{
    board = bd;
    playMoveAssumeLegal(board, co, x, y);
    col = -co;
}
//returns child that matches the input
Node *Node::playermove(vector<vector<int>> &target)
{
    if (!haschild)
        return this;
    while (children[0].board != target)
        children.pop_front();
    children.resize(1);
    return &children[0];
}
//return UCB
float Node::UCB(int &N)
{
    if (gameover == col)
        return -INFINITY;
    else if (gameover == -col)
        return INFINITY;
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
//build the moves vector, pass if needed
void Node::getmoves()
{
    haschild = true;
    legalMoves(board, col, moves);
    if (moves.size() == 0)
        if (!won(board)[1])
        {
            Node kid(board, -col);
            children.push_back(kid);
        }
}
int Node::explore()
{
    int index;
    bool newmove = false;
    {
        std::lock_guard<std::mutex> lock(this->child_mtx);
        if (!haschild)
            getmoves();
        if (moves.size())
        {
            index = children.size();
            int i = rand() % moves.size();
            Node kid(board, moves[i][0], moves[i][1], col);
            moves.erase(moves.begin() + i);
            children.push_back(kid);
            newmove = true;
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
        int outcome = children[index].explore();
        std::lock_guard<std::mutex> lock(mtx);
        if (!newmove)
            gameover = children[index].gameover;
        totalgames++;
        wins += (outcome == col);
        return outcome;
    }
}
//return greatest UCB child number
int Node::select()
{
    float ucbmax = 0;
    float ucb;
    int childsize = children.size();
    int imax = childsize - 1;
    for (int i = 0; i < childsize; i++)
    {
        ucb = children[i].UCB(totalgames);
        if (ucb > ucbmax)
        {
            ucbmax = ucb;
            imax = i;
        }
    }
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