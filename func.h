#include <array>
#include <deque>
#include <vector>
#include <random>
using namespace std;

int vialeft(array<array<int, 8>, 8> &board, int col, int i, int j);
int viaright(array<array<int, 8>, 8> &board, int col, int i, int j);
int viaup(array<array<int, 8>, 8> &board, int col, int i, int j);
int viadown(array<array<int, 8>, 8> &board, int col, int i, int j);
int upright(array<array<int, 8>, 8> &board, int col, int i, int j);
int upleft(array<array<int, 8>, 8> &board, int &col, int i, int j);
int downright(array<array<int, 8>, 8> &board, int &col, int i, int j);
int downleft(array<array<int, 8>, 8> &board, int &col, int i, int j);

bool legal(array<array<int, 8>, 8> &board, int col, int i, int j);

void playMoveAssumeLegal(array<array<int, 8>, 8> &board, int col, int i, int j);

void legalMoves(array<array<int, 8>, 8> &board, int col, array<pair<int, int>, 24> &ret, int &haschild);

void printboard(array<array<int, 8>, 8> &board);

vector<int> won(array<array<int, 8>, 8> &board);