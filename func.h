#include <vector>
using namespace std;

int vialeft(vector<vector<int>> &board, int col, int i, int j);
int viaright(vector<vector<int>> &board, int col, int i, int j);
int viaup(vector<vector<int>> &board, int col, int i, int j);
int viadown(vector<vector<int>> &board, int col, int i, int j);
int upright(vector<vector<int>> &board, int col, int i, int j);
int upleft(vector<vector<int>> &board, int &col, int i, int j);
int downright(vector<vector<int>> &board, int &col, int i, int j);
int downleft(vector<vector<int>> &board, int &col, int i, int j);

bool legal(vector<vector<int>> &board, int col, int i, int j);

void playMoveAssumeLegal(vector<vector<int>> &board, int col, int i, int j);

void legalMoves(vector<vector<int>> &board, int col, vector<vector<int>> &ret);

void printboard(vector<vector<int>> &board);

vector<int> won(vector<vector<int>> &board);

int playout(vector<vector<int>> board, int col);
