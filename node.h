#ifndef __node_h__
#define __node_h__
#include "config"
#include <deque>
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
    int8_t col;
    int8_t RdId;
    int8_t moveIndex = BoardSize - 1;
    int8_t gameover = -2;
    int totalScore = 0;
    int totalGames = 0;
    int8_t board[BoardSize];
    deque<Node> children;

    Node();
    Node(int8_t *bd, int8_t co);

    void clean();

    Node *getNewChild();
    float UCB(int N, int8_t co);
    Node *select();

    int explore(int8_t heat);
};
#endif