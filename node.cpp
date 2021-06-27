#include "func.h"
#include "node.h"
#include <mutex>
#include <math.h>
#include <vector>
using namespace std;

Node::Node() {}
Node::Node(const Node &t)
{
    col = t.col;
    board = t.board;
}
Node::Node(vector<vector<int>> &bd, int &x, int &y, int co)
{
    board = bd;
    playMoveAssumeLegal(board, co, x, y);
    col = -co;
}
//input map and the color of next step
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
        float a = global_C * sqrt(log(N) / (float)totalgames);
        a += ((float)(totalgames - wins) / totalgames);
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
//build the children vector
void Node::getchild()
{
    vector<vector<int>> moves;
    legalMoves(board, col, moves);
    if (moves.size())
    {
        //not pass then generate children
        for (int i = 0; i < moves.size(); i++)
        {
            Node kid(board, moves[i][0], moves[i][1], col);
            children.push_back(kid);
        }
    }
    else
    {
        vector<int> win = won(board);
        if (win[1])
        {
            gameover = win[0];
            return;
        }
        Node kid(board, -col);
        children.push_back(kid);
    }
    haschild = true;
}
//explore this node, col of computer step
int Node::explore()
{
    int ret = -2;
    {
        std::lock_guard<std::mutex> lock(this->child_mtx);
        if (haschild)
            ret = children[select()].explore();
        else if (gameover == -2)
            getchild();
    }
    if (ret == -2)
        ret = playout(board, col);
    std::lock_guard<std::mutex> lock(this->mtx);
    totalgames++;
    wins += (ret == col);
    return ret;
}
//return greatest UCB child number
int Node::select()
{
    //explored, go take care of child
    float ucbmax = 0;
    float ucb;
    int imax = 0;
    int childsize = children.size();
    //find the greatest UCB
    for (int i = 0; i < childsize; i++)
    {
        ucb = children[i].UCB(totalgames);
        if (ucb > ucbmax)
        {
            ucbmax = ucb;
            imax = i;
        }
        else if (ucb == ucbmax && rand() % children.size() == 0)
            imax = i;
    }
    return imax;
}
//return best board
Node *Node::getbest()
{
    //explored, go take care of child
    int ucbmax = 0;
    int imax = 0;
    int childsize = children.size();
    //find the greatest UCB
    for (int i = 0; i < childsize; i++)
    {
        int ucb = children[i].totalgames;
        if (ucb > ucbmax)
        {
            ucbmax = ucb;
            imax = i;
        }
    }
    for (int i = 0; i < imax; i++)
        children.pop_front();
    children.resize(1);
    return &children[0];
}