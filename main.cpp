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
array<int8_t, 64> GetStep(array<int8_t, 64> board, int &thinkTime, int threadCount, Node *&root)
{
    //set the root
    root = root->playermove(board);
    root->clean();

    time_t timeLimit = time(0) + thinkTime;
    //initialize thread
    vector<thread> threadvec;
    for (int i = 0; i < threadCount; i++)
        threadvec.emplace_back(Countdown, timeLimit, root);
    //after 5 seconds
    for (int i = 0; i < threadCount; i++)
        threadvec[i].join();

    cout << "Total playouts: " << root->totalgames << endl;
    cout << (root->col == 1 ? "Black " : "White ");
    root = root->getbest();
    float winrate = float(root->wins) / root->totalgames;
    if (winrate == 0 || winrate == 1 || root->gameover != -2)
        thinkTime = 0;
    cout << "winrate estimate: " << 1 - winrate << endl;
    return root->board;
}

int main()
{
    int timeLimit = 200;
    cout << "timeLimit\n";
    cin >> timeLimit;
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
        printboard(board);
    }
    cout << "Winner: " << (won(board)[0] == 1 ? "Black" : "White") << endl;
    return 0;
}