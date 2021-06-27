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

Node Source;
Node *root;

//continue exploring until time up
void Countdown(time_t timeLimit, Node *comp2)
{
    while (time(0) < timeLimit)
        comp2->explore();
    return;
}

vector<vector<int>> GetStep(vector<vector<int>> &board, bool is_black)
{
    //set the root
    root = root->playermove(board);
    root->clean();

    time_t timeLimit = time(0) + ThinkTime;
    //initialize thread
    vector<thread> threadvec;
    for (int i = 0; i < threadCount; i++)
        threadvec.emplace_back(Countdown, timeLimit, root);
    //after 5 seconds
    for (int i = 0; i < threadCount; i++)
        threadvec[i].join();

    cout << "Total playouts: " << root->totalgames << endl;
    root = root->getbest();
    float winrate = float(root->wins) / root->totalgames;
    cout << "Player wins: " << root->wins << endl;
    cout << "Player winrate estimate: " << winrate << endl;
    if (winrate == 0)
        ThinkTime = 0;
    return root->board;
}

int main()
{
    //default 8 thread
    threadCount = 8;
    cout << "How much time can the computer think?(seconds)\n";
    cin >> ThinkTime;
    bool IsBlack = true;
    vector<vector<int>> board{{0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 1, -1, 0, 0, 0},
                              {0, 0, 0, -1, 1, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0}};
    Source.board = board;
    Source.col = IsBlack ? 1 : -1;
    root = &Source;
    while (won(board)[1] == 0)
    {
        if (IsBlack)
            board = GetStep(board, IsBlack);
        else
            board = root->children[rand() % root->children.size()].board;
        IsBlack = !IsBlack;
        printboard(board);
        cout << endl;
    }
    if (won(board)[0] > 0)
        cout << "winner: @\n";
    else
        cout << "winner: O\n";

    cout << "gameover: " << root->gameover << endl;
    return 0;
}