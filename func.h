#ifndef __func_h__
#define __func_h__
#include "config"
#include <cstdint>
using namespace std;

extern int8_t Ishuffled[BoardSize * BoardSize];
extern int8_t Jshuffled[BoardSize * BoardSize];

void tryleft(int8_t board[BoardSize], int8_t color, int8_t i, int8_t j, bool &legal);
void tryright(int8_t board[BoardSize], int8_t color, int8_t i, int8_t j, bool &legal);
void tryup(int8_t board[BoardSize], int8_t color, int8_t i, int8_t j, bool &legal);
void trydown(int8_t board[BoardSize], int8_t color, int8_t i, int8_t j, bool &legal);
void upright(int8_t board[BoardSize], int8_t color, int8_t i, int8_t j, bool &legal);
void upleft(int8_t board[BoardSize], int8_t color, int8_t i, int8_t j, bool &legal);
void downright(int8_t board[BoardSize], int8_t color, int8_t i, int8_t j, bool &legal);
void downleft(int8_t board[BoardSize], int8_t color, int8_t i, int8_t j, bool &legal);

bool tryMove(int8_t board[BoardSize], int8_t color, int8_t i, int8_t j);

bool newMove(int8_t board[BoardSize], int8_t color, int8_t shuffleID, int8_t &moveIndex);

bool hasMove(int8_t board[BoardSize], int8_t color);

int score(int8_t board[BoardSize]);

int playout(int8_t board[BoardSize], int8_t color);
#endif