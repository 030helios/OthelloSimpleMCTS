#include <vector>
using namespace std;

int vialeft(vector<vector<int>> &board, int col, int x, int y);
int viaright(vector<vector<int>> &board, int col, int x, int y);
int viaup(vector<vector<int>> &board, int col, int x, int y);
int viadown(vector<vector<int>> &board, int col, int x, int y);
int upright(vector<vector<int>> &board, int col, int x, int y);
int upleft(vector<vector<int>> &board, int &col, int i, int j);
int downright(vector<vector<int>> &board, int &col, int i, int j);
int downleft(vector<vector<int>> &board, int &col, int i, int j);

int viable(vector<vector<int>> &board, int &col, int i, int j);

int puthere(vector<vector<int>> &board, int col, int x, int y);

void givelist(vector<vector<int>> &board, int col, vector<vector<int>> &ret);

int printboard(vector<vector<int>> &board);

vector<int> won(vector<vector<int>> &board);

int randomstep(vector<vector<int>> &board, int col);
