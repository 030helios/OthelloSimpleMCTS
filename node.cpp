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
//init with move to generate child node
Node::Node(vector<vector<int>> &bd, int &x, int &y, int co)
{
    board = bd;
    playMoveAssumeLegal(board, co, x, y);
    col = -co;
}
//init as pass
Node::Node(vector<vector<int>> &bd, int co)
{
    col = co;
    board = bd;
}
//returns child that matches the input
Node *Node::playermove(vector<vector<int>> &target)
{
    if (haschild)
    {
        while (children[0].board != target)
            children.pop_front();
        children.resize(1);
        return &children[0];
    }
    return this;
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
    return INFINITY;
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
    {
        if (won(board)[1])
            return;
        Node kid(board, -col);
        children.push_back(kid);
    }
}
//explore this node, col of computer step
int Node::explore()
{
    int index;
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
        }
        else
            index = select();
    }
    int winCol;
    if (index == -1)
    {
        winCol = won(board)[0];
        gameover = winCol;
    }
    else
        winCol = children[index].explore();

    std::lock_guard<std::mutex> lock(mtx);
    totalgames++;
    wins += (winCol == col);
    return winCol;
}
//return greatest UCB child number
int Node::select()
{
    //explored, go take care of child
    float ucbmax = 0;
    float ucb;
    int childsize = children.size();
    int imax = childsize - 1;
    //find the greatest UCB
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
    //explored, go take care of child
    int maxGames = 0;
    int imax = 0;
    int childsize = children.size();
    //find the greatest UCB
    for (int i = 0; i < childsize; i++)
    {
        int games = children[i].totalgames;
        if (games > maxGames)
        {
            maxGames = games;
            imax = i;
        }
    }
    for (int i = 0; i < imax; i++)
        children.pop_front();
    children.resize(1);
    return &children[0];
}