#ifndef __func_h__
#define __func_h__
#include "config"
#include <array>
#include <vector>
#include <random>
#include <cstring>
using namespace std;

extern array<array<pair<int8_t, int8_t>, BoardSize>, BoardSize> RdMoves;

int toleft(array<int8_t, BoardSize> &board, int8_t &col, int i, int j);
int toright(array<int8_t, BoardSize> &board, int8_t &col, int i, int j);
int toup(array<int8_t, BoardSize> &board, int8_t &col, int i, int j);
int todown(array<int8_t, BoardSize> &board, int8_t &col, int i, int j);
int upright(array<int8_t, BoardSize> &board, int8_t &col, int i, int j);
int upleft(array<int8_t, BoardSize> &board, int8_t &col, int i, int j);
int downright(array<int8_t, BoardSize> &board, int8_t &col, int i, int j);
int downleft(array<int8_t, BoardSize> &board, int8_t &col, int i, int j);

bool tryMove(array<int8_t, BoardSize> &board, int8_t &col, int x, int y);

bool newMove(array<int8_t, BoardSize> &board, int8_t &col, int8_t &RdId, int8_t &moveIndex);

void printboard(array<int8_t, BoardSize> board, string name);

bool hasMove(array<int8_t, BoardSize> board, int8_t col);

vector<int> won(array<int8_t, BoardSize> &board);
#endif