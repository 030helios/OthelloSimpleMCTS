#ifndef __node_h__
#define __node_h__
#include "config"
#include <vector>
#include <math.h>
#include <random>
#include <cstdint>
#include <semaphore.h>
using namespace std;

class Node
{
private:
    sem_t sem;

public:
    int8_t color;
    int8_t shuffleID;
    int8_t moveIndex = BoardSize - 1;
    int8_t gameover = -2;
    int totalScore = 0;
    int totalGames = 0;
    int8_t board[BoardSize];
    vector<Node *> children;

    ~Node();
    Node(int8_t *bd, int8_t col);

    void clean();

    Node *getNewChild();
    float UCB(int N, int8_t col);
    Node *select();

    int explore(int8_t heat);
};
#endif