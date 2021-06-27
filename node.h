#include <mutex>
#include <vector>
#include <deque>
using namespace std;

#define global_C 0.6

//the tree node  of MCTS
class Node
{
private:
    mutex mtx;
    mutex child_mtx;
public:
    int col;
    bool haschild = false;
    int gameover = -2;
    int wins = 0;
    int totalgames = 0;
    vector<vector<int>> board;
    vector<vector<int>> moves;
    deque<Node> children;

    Node();
    Node(const Node &t);
    Node(vector<vector<int>> &bd, int co);
    Node(vector<vector<int>> &bd, int &x, int &y, int co);

    Node *playermove(vector<vector<int>> &target);
    float UCB(int &N);

    void clean();
    void getmoves();

    int explore();
    int select();
    Node *getbest();
};
