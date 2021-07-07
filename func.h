#ifndef __func_h__
#define __func_h__
#include "config"
#include <array>
using namespace std;

extern array<array<pair<int8_t, int8_t>, BoardSize>, BoardSize> shuffledMoves;

void tryleft(array<int8_t, BoardSize> &board, int8_t col, int8_t i, int8_t j, bool &legal);
void tryright(array<int8_t, BoardSize> &board, int8_t col, int8_t i, int8_t j, bool &legal);
void tryup(array<int8_t, BoardSize> &board, int8_t col, int8_t i, int8_t j, bool &legal);
void trydown(array<int8_t, BoardSize> &board, int8_t col, int8_t i, int8_t j, bool &legal);
void upright(array<int8_t, BoardSize> &board, int8_t col, int8_t i, int8_t j, bool &legal);
void upleft(array<int8_t, BoardSize> &board, int8_t col, int8_t i, int8_t j, bool &legal);
void downright(array<int8_t, BoardSize> &board, int8_t col, int8_t i, int8_t j, bool &legal);
void downleft(array<int8_t, BoardSize> &board, int8_t col, int8_t i, int8_t j, bool &legal);

bool tryMove(array<int8_t, BoardSize> &board, int8_t col, int8_t i, int8_t j);

bool newMove(array<int8_t, BoardSize> &board, int8_t col, int8_t RdId, int8_t &moveIndex);

bool hasMove(array<int8_t, BoardSize> board, int8_t col);

int score(array<int8_t, BoardSize> &board);

int playout(array<int8_t, BoardSize> board, int8_t col);
#endif