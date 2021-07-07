#include "func.h"
using namespace std;

void tryleft(array<int8_t, BoardSize> &board, int8_t col, int8_t i, int8_t j, bool &legal)
{
    int flip = 0; //the amount of stones we flip
    while (--j >= 0)
        if (board[i * EdgeSize + j] == 0)
            return;
        else if (board[i * EdgeSize + j] == col)
        {
            if (flip)
                legal = true;
            while (flip--)
                board[i * EdgeSize + ++j] = col;
            return;
        }
        else
            flip++;
}
void tryright(array<int8_t, BoardSize> &board, int8_t col, int8_t i, int8_t j, bool &legal)
{
    int flip = 0; //the amount of stones we flip
    while (++j < EdgeSize)
        if (board[i * EdgeSize + j] == 0)
            return;
        else if (board[i * EdgeSize + j] == col)
        {
            if (flip)
                legal = true;
            while (flip--)
                board[i * EdgeSize + --j] = col;
            return;
        }
        else
            flip++;
}
void tryup(array<int8_t, BoardSize> &board, int8_t col, int8_t i, int8_t j, bool &legal)
{
    int flip = 0; //the amount of stones we flip
    while (--i >= 0)
        if (board[i * EdgeSize + j] == 0)
            return;
        else if (board[i * EdgeSize + j] == col)
        {
            if (flip)
                legal = true;
            while (flip--)
                board[++i * EdgeSize + j] = col;
            return;
        }
        else
            flip++;
}
void trydown(array<int8_t, BoardSize> &board, int8_t col, int8_t i, int8_t j, bool &legal)
{
    int flip = 0; //the amount of stones we flip
    while (++i < EdgeSize)
        if (board[i * EdgeSize + j] == 0)
            return;
        else if (board[i * EdgeSize + j] == col)
        {
            if (flip)
                legal = true;
            while (flip--)
                board[--i * EdgeSize + j] = col;
            return;
        }
        else
            flip++;
}
void upright(array<int8_t, BoardSize> &board, int8_t col, int8_t i, int8_t j, bool &legal)
{
    int flip = 0; //the amount of stones we flip
    while (--i >= 0 && ++j < EdgeSize)
        if (board[i * EdgeSize + j] == 0)
            return;
        else if (board[i * EdgeSize + j] == col)
        {
            if (flip)
                legal = true;
            while (flip--)
                board[++i * EdgeSize + --j] = col;
            return;
        }
        else
            flip++;
}
void upleft(array<int8_t, BoardSize> &board, int8_t col, int8_t i, int8_t j, bool &legal)
{
    int flip = 0; //the amount of stones we flip
    while (--i >= 0 && --j >= 0)
        if (board[i * EdgeSize + j] == 0)
            return;
        else if (board[i * EdgeSize + j] == col)
        {
            if (flip)
                legal = true;
            while (flip--)
                board[++i * EdgeSize + ++j] = col;
            return;
        }
        else
            flip++;
}
void downright(array<int8_t, BoardSize> &board, int8_t col, int8_t i, int8_t j, bool &legal)
{
    int flip = 0; //the amount of stones we flip
    while (++i < EdgeSize && ++j < EdgeSize)
        if (board[i * EdgeSize + j] == 0)
            return;
        else if (board[i * EdgeSize + j] == col)
        {
            if (flip)
                legal = true;
            while (flip--)
                board[--i * EdgeSize + --j] = col;
            return;
        }
        else
            flip++;
}
void downleft(array<int8_t, BoardSize> &board, int8_t col, int8_t i, int8_t j, bool &legal)
{
    int flip = 0; //the amount of stones we flip
    while (++i < EdgeSize && --j >= 0)
        if (board[i * EdgeSize + j] == 0)
            return;
        else if (board[i * EdgeSize + j] == col)
        {
            if (flip)
                legal = true;
            while (flip--)
                board[--i * EdgeSize + ++j] = col;
            return;
        }
        else
            flip++;
}
//Attempts a move on the position i,j. Returns true and changes the board if such move is legal.
bool tryMove(array<int8_t, BoardSize> &board, int8_t col, int8_t i, int8_t j)
{
    if (board[i * EdgeSize + j] != 0)
        return false;
    bool legal = false;
    if (j > 1)
        tryleft(board, col, i, j, legal);
    if (j < (EdgeSize - 2))
        tryright(board, col, i, j, legal);
    if (i > 1)
        tryup(board, col, i, j, legal);
    if (i < (EdgeSize - 2))
        trydown(board, col, i, j, legal);
    if (i > 1 && j < (EdgeSize - 2))
        upright(board, col, i, j, legal);
    if (i > 1 && j > 1)
        upleft(board, col, i, j, legal);
    if (i < (EdgeSize - 2) && j < (EdgeSize - 2))
        downright(board, col, i, j, legal);
    if (i < (EdgeSize - 2) && j > 1)
        downleft(board, col, i, j, legal);
    if (legal)
        board[i * EdgeSize + j] = col;
    return legal;
}
//Returns true if we made a move
bool newMove(array<int8_t, BoardSize> &board, int8_t col, int8_t RdId, int8_t &moveIndex)
{
    array<pair<int8_t, int8_t>, BoardSize> &MoveArr = shuffledMoves[RdId];
    while (!tryMove(board, col, MoveArr[moveIndex].first, MoveArr[moveIndex].second))
        if (--moveIndex < 0)
            return false;
    moveIndex--;
    return true;
}
bool hasMove(array<int8_t, BoardSize> board, int8_t col)
{
    int8_t moveIndex = BoardSize - 1;
    return newMove(board, col, 0, moveIndex);
}
int score(array<int8_t, BoardSize> &board)
{
    int ret = 0;
    for (auto stone : board)
        ret += stone;
    ret = (ret > 0) - (ret < 0);
    return ret;
}
//Makes random moves, returns the outcome of the game
int playout(array<int8_t, BoardSize> board, int8_t col)
{
    while (1)
    {
        int8_t moveInd = BoardSize - 1;
        if (!newMove(board, col, rand() % BoardSize, moveInd))
            if (!hasMove(board, -col))
                break;
        col = -col;
    }
    return score(board);
}