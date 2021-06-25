#include <mutex>
#include <vector>
using namespace std;

float global_C = 0.6;

//the tree node  of MCTS
class Node
{
private:
    mutex stats_mtx;
    mutex child_mtx;
    mutex explore_mtx;

public:
    int col;
    int haschild = 0;
    int explored = 0;
    int wins = 0;
    int totalgames = 0;
    int initwin = 0;
    vector<int> step;
    vector<vector<int>> board;
    vector<Node> children;

    Node(const Node &t);
    Node();

    int gethaschild();
    int getexplored();
    Node *playermove(vector<vector<int>> &target, bool &newSource);
    float UCB(int &N);

    void start(vector<vector<int>> &bd, int &x, int &y, int co);
    void pass(vector<vector<int>> &bd, int co);

    int clean();
    void getchild();
    void play2win();

    int randstep();
    int update();
    void explore();
    int select();
    Node *getbest();
};
