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
array<array<int8_t, 8>, 8> GetStep(array<array<int8_t, 8>, 8> board, int &ThinkTime, int threadCount, Node *&root)
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
    int timeLimit;
    cout << "How much time can the computer think?(seconds)\n";
    cin >> timeLimit;
    //black
    int computerColor = 1;
    array<array<int8_t, 8>, 8> board{{0, 0, 0, 0, 0, 0, 0, 0,
                                   0, 0, 0, 0, 0, 0, 0, 0,
                                   0, 0, 0, 0, 0, 0, 0, 0,
                                   0, 0, 0, 1, -1, 0, 0, 0,
                                   0, 0, 0, -1, 1, 0, 0, 0,
                                   0, 0, 0, 0, 0, 0, 0, 0,
                                   0, 0, 0, 0, 0, 0, 0, 0,
                                   0, 0, 0, 0, 0, 0, 0, 0}};
    Node Source(board, computerColor);
    Node *root = &Source;
    while (won(board)[1] == 0)
    {
        //default 8 thread
        board = GetStep(board, timeLimit, 8, root);
        printboard(board);
        board = root->children[rand() % root->children.size()].board;
        printboard(board);
    }
    if (won(board)[0] == 0)
        cout << "draw\n";
    else
        cout << "winner: " << (won(board)[0] < 0) ? "O\n" : "@\n";
    return 0;
}