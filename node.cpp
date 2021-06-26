#include "func.h"
#include "node.h"
#include <mutex>
#include <math.h>
#include <vector>
using namespace std;

Node::Node(const Node &t)
{
    col = t.col;
    haschild = false;
    explored = false;
    wins = 0;
    totalgames = 0;
    initwin = 0;
    board = t.board;
}
Node::Node()
{
    haschild = false;
    explored = false;
    wins = 0;
    totalgames = 0;
    initwin = 0;
}
bool Node::gethaschild()
{
    std::lock_guard<std::mutex> lock(this->stats_mtx);
    return haschild;
}
bool Node::getexplored()
{
    std::lock_guard<std::mutex> lock(this->stats_mtx);
    return explored;
}

//returns next node
Node *Node::playermove(vector<vector<int>> &target, bool &newSource)
{
    int ind = -1;
    if (!haschild)
        getchild();
    //see which child matches the input
    for (int i = 0; i < children.size(); i++)
    {
        if (children[i].board == target)
        {
            ind = i;
        }
    }
    //if error and target is not in children
    if (ind == -1)
    {
        newSource = true;
        return this;
    }
    children.resize(ind + 1);
    return &children[ind];
}
//return UCB
float Node::UCB(int &N)
{
    float a = global_C * sqrt((log(N)) / ((float)totalgames));
    a += ((float)(totalgames - wins) / (totalgames));
    return a;
}
void Node::start(vector<vector<int>> &bd, int &x, int &y, int co)
{
    board = bd;
    puthere(board, co, x, y);
    col = -co;
}
//input map and the color of next step
void Node::pass(vector<vector<int>> &bd, int co)
{
    vector<int> stepu(2, 0);
    col = co;
    board = bd;
}
//removes data without removing the structure
int Node::clean()
{
    wins = 0;
    totalgames = 0;
    initwin = 0;
    explored = false;
    return 0;
}
//build the children vector
void Node::getchild()
{
    vector<vector<int>> coords;
    givelist(board, col, coords);
    Node kid;
    if (coords.size())
    {
        children.reserve(coords.size());
        //not pass then generate children
        for (int i = 0; i < coords.size(); i++)
        {
            kid.start(board, coords[i][0], coords[i][1], col);
            children.push_back(kid);
        }
    }
    else
    {
        kid.pass(board, -col);
        children.push_back(kid);
    }
}
//initiate process
void Node::play2win()
{
    totalgames += 1;
    wins += (randstep() == col);
    if (totalgames == 1)
        initwin = wins;
}
//random choices return win or not, col of next step
int Node::randstep()
{
    //if reach an end
    if (children.size() == 0)
    {
        vector<vector<int>> bd = board;
        return randomstep(bd, col);
    }
    //if there's children
    int ran = rand() % children.size();
    return children[ran].randstep();
}
//update the total games and wins;
int Node::update()
{
    int childsize = children.size();
    wins = 0;
    totalgames = 0;
    for (int i = 0; i < childsize; i++)
    {
        totalgames += children[i].totalgames;
        wins += children[i].wins;
    }
    wins = totalgames - wins;
    wins += initwin;
    totalgames++;
    return 0;
}

//explore this node, col of computer step
void Node::explore()
{
    if (gethaschild() && getexplored())
    {
        children[select()].explore();
        std::lock_guard<std::mutex> lock(this->stats_mtx);
        update();
        return;
    }
    std::lock_guard<std::mutex> lock(this->stats_mtx);
    if (!gethaschild())
    {
        //first time generating children
        if (won(board)[1])
            play2win();
        else
        {
            haschild = true;
            getchild();
            for (int i = 0; i < children.size(); i++)
            {
                children[i].play2win();
            }
            update();
        }
    }
    else if (!getexplored())
    {
        //second time
        explored = true;
        for (int i = 0; i < children.size(); i++)
        {
            children[i].clean();
            children[i].play2win();
        }
        update();
    }
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
    children.resize(imax + 1);
    return &children[imax];
}
