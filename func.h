#include <array>
#include <deque>
#include <vector>
#include <random>
#include <iostream>
#include <cstring>
using namespace std;

int vialeft(array<int8_t, 64> &board, int8_t &col, int i, int j);
int viaright(array<int8_t, 64> &board, int8_t &col, int i, int j);
int viaup(array<int8_t, 64> &board, int8_t &col, int i, int j);
int viadown(array<int8_t, 64> &board, int8_t &col, int i, int j);
int upright(array<int8_t, 64> &board, int8_t &col, int i, int j);
int upleft(array<int8_t, 64> &board, int8_t &col, int i, int j);
int downright(array<int8_t, 64> &board, int8_t &col, int i, int j);
int downleft(array<int8_t, 64> &board, int8_t &col, int i, int j);

bool legal(array<int8_t, 64> &board, int8_t &col, int i, int j);

void playMoveAssumeLegal(array<int8_t, 64> &board, int8_t &col, int i, int j);

void legalMoves(array<int8_t, 64> &board, int8_t &col, array<pair<int8_t, int8_t>, 25> &ret, int8_t &haschild);

void printboard(array<int8_t, 64> board);

vector<int> won(array<int8_t, 64> &board);