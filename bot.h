#ifndef __bot_h__
#define __bot_h__
#include "node.h"
#include <chrono>
#include <thread>
#include <vector>
#include <cstdint>
using namespace std;
using namespace chrono;

class Bot
{
    Node source; // won't change
    Node *root;  // will change after GetStep
    // Default heat value for root exploration.
    // Depends on clock rate, thinkTime and threadCount, which leaves room for improvement.
    float depth;
    milliseconds timeLimit;
    int threadCount;
    vector<thread> threadVec;

    static void trim(Node *parent, Node *keep);
    static void countdown(system_clock::time_point start, milliseconds thinkTime, Node *root, float depth, int threadCount);

    void move();
    void enemyMove(int8_t target[BoardSize]);

public:
    ~Bot();
    Bot(int tLimit, int thrCount, int8_t board[BoardSize], int8_t color);

    void Log(ostream &out);
    int8_t *play(int8_t board[BoardSize]);
};
#endif