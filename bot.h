#ifndef __bot_h__
#define __bot_h__
#include "node.h"
#include <chrono>
#include <thread>
#include <vector>
using namespace std;
using namespace chrono;

class Bot
{
    Node source; //won't change
    Node *root;  //will change after GetStep
    // Default heat value for root exploration.
    // Depends on clock rate, thinkTime and threadCount, which leaves room for improvement.
    float depth;
    int timeLimit;
    int threadCount;
    vector<thread> threadVec;

    static void trim(Node *parent, Node *keep);
    static void countdown(system_clock::time_point start, milliseconds thinkTime, Node *root, float depth, int threadCount);

    void move();
    void enemyMove(array<int8_t, BoardSize> &target);

public:
    ~Bot();
    Bot(int timeLimit, int threadCount, array<int8_t, BoardSize> board, int8_t color);
    array<int8_t, BoardSize> play(array<int8_t, BoardSize> board);
};
#endif