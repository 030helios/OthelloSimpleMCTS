#include <mutex>
#include <vector>
using namespace std;

#define global_C 0.6

//the tree node  of MCTS
class Node
{
private:
    mutex mtx;

public:
    int col;
    bool haschild = false;
    bool explored = false;
    int wins = 0;
    int totalgames = 0;
    int initwin = 0;
    vector<vector<int>> board;
    vector<Node> children;

    Node(const Node &t);
    Node();

    Node *playermove(vector<vector<int>> &target, bool &newSource);
    float UCB(int &N);

    void start(vector<vector<int>> &bd, int &x, int &y, int co);
    void pass(vector<vector<int>> &bd, int co);

    void clean();
    void getchild();
    void play2win();

    int randstep();
    void update();
    void explore();
    int select();
    Node *getbest();
};
