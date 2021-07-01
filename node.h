#ifndef __node_h__
#define __node_h__
#include "config"
#include <mutex>
#include <array>
#include <deque>
#include <math.h>
#include <utility>
#include <algorithm>
using namespace std;

class Node
{
private:
    mutex mtx;

public:
    int8_t col;
    int8_t RdId;
    int8_t moveIndex = BoardSize - 1;
    int8_t gameover = -2;
    int wins = 0;
    int totalgames = 0;
    array<int8_t, BoardSize> board;
    deque<Node> children;

    Node();
    Node(const Node &t);
    Node(array<int8_t, BoardSize> &bd, int8_t co);

    float UCB(int &N, int8_t co);

    void clean();

    int8_t explore();
    Node *select();
    Node *getbest();
    Node *playermove(array<int8_t, BoardSize> &target);
};
#endif