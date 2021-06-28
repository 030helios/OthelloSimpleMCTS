#include "func.h"
#include "node.h"
#include <time.h>
#include <math.h>
#include <random>
#include <thread>
#include <stdlib.h>
#include <iostream>
using namespace std;

//continue exploring until time up
void Countdown(time_t timeLimit, Node *root)
{
    while (time(0) < timeLimit)
        root->explore();
    return;
}
array<int8_t, 64> GetStep(array<int8_t, 64> board, int &ThinkTime, int threadCount, Node *&root)
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
    int timeLimit = 2;
    //black
    int computerColor = 1;
    array<int8_t, 64> board{0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 1, -1, 0, 0, 0,
                            0, 0, 0, -1, 1, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 0};
    Node Source(board, computerColor);
    Node *root = &Source;
    vector<thread> threadvec;
    while (won(board)[1] == 0)
    {
        //default 8 thread
        board = GetStep(board, timeLimit, 8, root);
        for (int i = 0; i < threadvec.size(); i++)
            threadvec[i].join();
        threadvec.clear();
        threadvec.emplace_back(printboard, board);
        board = root->children[rand() % root->children.size()].board;
        for (int i = 0; i < threadvec.size(); i++)
            threadvec[i].join();
        threadvec.clear();
        threadvec.emplace_back(printboard, board);
        cout << endl;
    }
    return 0;
}