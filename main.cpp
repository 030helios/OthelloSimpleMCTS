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

int ThinkTime;
int threadCount;

//vector of root
vector<Node *> roots;

bool newSource = true;
Node Source;

//continue exploring until time up
void Countdown(time_t timeLimit, Node *comp2)
{
    comp2->clean();
    while (time(0) < timeLimit)
        comp2->explore();
    return;
}

vector<vector<int>> GetStep(vector<vector<int>> &board, bool is_black)
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
        roots.clear();
        for (int i = 0; i < threadCount; i++)
            roots.push_back(&Source);
    }

    time_t timeLimit = time(0) + ThinkTime;
    //initialize thread
    vector<thread> threadvec;
    for (int i = 0; i < threadCount; i++)
        threadvec.emplace_back(Countdown, timeLimit, roots[i]);
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
    cout<<"Total playouts: "<<roots[0]->totalgames<<endl;
    Node *NewRoot = &roots[0]->children[ind];
    for (int i = 0; i < threadCount; i++)
        roots[i] = NewRoot;
    float winrate = float(NewRoot->wins)/NewRoot->totalgames;
    cout<<"Player winrate estimate: "<<winrate<<endl;
    return roots[0]->board;
}

int main()
{
    //default 7 thread
    threadCount = 7;
    cout<<"How much time can the computer think?(seconds)\n";
    cin>>ThinkTime;
    bool IsBlack = true;
    vector<vector<int>> board{{0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 1,-1, 0, 0, 0},
                              {0, 0, 0,-1, 1, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0}};
    while(won(board)[1]==0){
        printboard(board);
        cout<<endl;
        board = GetStep(board,IsBlack);
        printboard(board);
        cout<<endl;
        if(won(board)[1]){
            break;
        }
        char y;
        int x;
        do
        {
            cout<<"Your turn, example: A 0"<<endl;
            cin>>y>>x;
        } while (!viable(board,IsBlack?-1:1,y-'A',x));
        puthere(board,IsBlack?-1:1,y-'A',x);
    }
    if(won(board)[0]>0)
        cout<<"winner: "<<"@\n";
    else
        cout<<"winner: "<<"O\n";
    return 0;
}