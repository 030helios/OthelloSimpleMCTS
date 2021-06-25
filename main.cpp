#include "func.h"
#include "node.h"
#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <math.h>
#include <vector>
#include <random>
#include <thread>
#include <mutex>
using namespace std;

bool newSource = true;
int threadCount = 7;
//
Node Source;
//vector of root
vector<Node *> roots;

//real part
void FiveSec(time_t timeLimit, Node *comp2)
{
    comp2->clean();
    while (time(0) < timeLimit)
        comp2->explore();
    return;
}

vector<int> GetStep(vector<vector<int>> &board, bool is_black)
{
    //set the roots
    if (!newSource)
    {
        Node *NewRoot = roots[0]->playermove(board, newSource);
        //get the new board
        for (int i = 0; i < threadCount; i++)
            roots[i] = NewRoot;
    }
    //first time or error, reset Source
    if (newSource)
    {
        newSource = false;
        int col = is_black ? 1 : -1;
        Source.pass(board, col);
        for (int i = 0; i < threadCount; i++)
            roots[i] = &Source;
    }

    //MCTS for 5 secs
    time_t timeLimit = time(0) + 5;
    //initialize thread
    vector<thread> threadvec;
    for (int i = 0; i < threadCount; i++)
        threadvec.emplace_back(FiveSec, timeLimit, roots[i]);
    //after 5 seconds
    for (int i = 0; i < threadCount; i++)
        threadvec[i].join();

    //find the best child
    int ind = 0;
    int childsize = roots[0]->children.size();
    int greatest_child_total = 0;
    for (int i = 0; i < childsize; i++)
    {
        if (greatest_child_total < roots[0]->children[i].totalgames)
        {
            ind = i;
            greatest_child_total = roots[0]->children[i].totalgames;
        }
    }
    //update each root
    Node *NewRoot = &roots[0]->children[ind];
    for (int i = 0; i < threadCount; i++)
        roots[i] = NewRoot;

    return roots[0]->step;
}

int main()
{
    vector<vector<int>> board{{0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 1,-1, 0, 0, 0},
                              {0, 0, 0,-1, 1, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0}};
    printboard(board);
    return 0;
}