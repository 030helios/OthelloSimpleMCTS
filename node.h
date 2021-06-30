#include "config"
#include <mutex>
#include <array>
#include <deque>
#include <math.h>
#include <utility>
#include <algorithm>
using namespace std;

//the tree node  of MCTS
class Node
{
private:
    mutex mtx;
    mutex child_mtx;

public:
    int8_t col;
    int8_t haschild = 0;
    int8_t gameover = -2;
    int wins = 0;
    int totalgames = 0;
    array<int8_t, BoardSize> board;
    array<pair<int8_t, int8_t>, 25> moves;
    deque<Node> children;

    Node();
    Node(const Node &t);
    Node(array<int8_t, BoardSize> &bd, int8_t co);
    Node(array<int8_t, BoardSize> &bd, int8_t &x, int8_t &y, int8_t co);

    Node *playermove(array<int8_t, BoardSize> &target);
    float UCB(int &N, int8_t co);

    void clean();
    void getmoves();

    int8_t explore();
    Node *select();
    Node *getbest();
};