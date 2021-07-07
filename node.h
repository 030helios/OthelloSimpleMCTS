#ifndef __node_h__
#define __node_h__
#include "config"
#include <array>
#include <deque>
#include <math.h>
#include <random>
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
    array<int8_t, BoardSize> board;
    deque<Node> children;

    Node();
    Node(array<int8_t, BoardSize> &bd, int8_t co);

    void clean();

    Node *getNewChild();
    float UCB(int N, int8_t co);
    Node *select();

    int explore(int8_t heat);
};
#endif