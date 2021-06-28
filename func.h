#include <array>
#include <deque>
#include <vector>
#include <random>
using namespace std;

int vialeft(array<array<int8_t, 8>, 8> &board, int col, int i, int j);
int viaright(array<array<int8_t, 8>, 8> &board, int col, int i, int j);
int viaup(array<array<int8_t, 8>, 8> &board, int col, int i, int j);
int viadown(array<array<int8_t, 8>, 8> &board, int col, int i, int j);
int upright(array<array<int8_t, 8>, 8> &board, int col, int i, int j);
int upleft(array<array<int8_t, 8>, 8> &board, int &col, int i, int j);
int downright(array<array<int8_t, 8>, 8> &board, int &col, int i, int j);
int downleft(array<array<int8_t, 8>, 8> &board, int &col, int i, int j);

bool legal(array<array<int8_t, 8>, 8> &board, int col, int i, int j);

void playMoveAssumeLegal(array<array<int8_t, 8>, 8> &board, int col, int i, int j);

void legalMoves(array<array<int8_t, 8>, 8> &board, int8_t col, array<pair<int8_t, int8_t>, 25> &ret, int8_t &haschild);

void printboard(array<array<int8_t, 8>, 8> &board);

vector<int> won(array<array<int8_t, 8>, 8> &board);