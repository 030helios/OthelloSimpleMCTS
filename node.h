#include <mutex>
#include <array>
#include <deque>
#include <utility>
using namespace std;

#define global_C 0.5

//the tree node  of MCTS
class Node
{
private:
    mutex mtx;
    mutex child_mtx;

public:
    int col;
    int haschild = 0;
    int gameover = -2;
    int wins = 0;
    int totalgames = 0;
    array<array<int, 8>, 8> board;
    array<pair<int, int>, 24> moves;
    deque<Node> children;

    Node();
    Node(const Node &t);
    Node(array<array<int, 8>, 8> &bd, int co);
    Node(array<array<int, 8>, 8> &bd, int &x, int &y, int co);

    Node *playermove(array<array<int, 8>, 8> &target);
    float UCB(int &N);

    void clean();
    void getmoves();

    int explore();
    int select();
    Node *getbest();
};