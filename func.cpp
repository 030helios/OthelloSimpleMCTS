#include "func.h"
#include <numeric>
#include <algorithm>
using namespace std;

void tryleft(int8_t board[BoardSize], int8_t col, int8_t i, int8_t j, bool &legal)
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
void tryright(int8_t board[BoardSize], int8_t col, int8_t i, int8_t j, bool &legal)
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
void tryup(int8_t board[BoardSize], int8_t col, int8_t i, int8_t j, bool &legal)
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
void trydown(int8_t board[BoardSize], int8_t col, int8_t i, int8_t j, bool &legal)
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
void upright(int8_t board[BoardSize], int8_t col, int8_t i, int8_t j, bool &legal)
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
void upleft(int8_t board[BoardSize], int8_t col, int8_t i, int8_t j, bool &legal)
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
void downright(int8_t board[BoardSize], int8_t col, int8_t i, int8_t j, bool &legal)
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
void downleft(int8_t board[BoardSize], int8_t col, int8_t i, int8_t j, bool &legal)
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
bool tryMove(int8_t board[BoardSize], int8_t col, int8_t i, int8_t j)
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
bool newMove(int8_t board[BoardSize], int8_t col, int8_t RdId, int8_t &moveIndex)
{
    int8_t *I = &Ishuffled[RdId * BoardSize];
    int8_t *J = &Jshuffled[RdId * BoardSize];
    while (!tryMove(board, col, I[moveIndex], J[moveIndex]))
        if (--moveIndex < 0)
            return false;
    moveIndex--;
    return true;
}
bool hasMove(int8_t board[BoardSize], int8_t col)
{
    int8_t newBoard[BoardSize];
    copy(board, board + BoardSize, newBoard);
    int8_t moveIndex = BoardSize - 1;
    return newMove(newBoard, col, 0, moveIndex);
}
int score(int8_t board[BoardSize])
{
    int ret = accumulate(board, board + BoardSize, 0);
    ret = (ret > 0) - (ret < 0);
    return ret;
}
//Makes random moves, returns the outcome of the game
int playout(int8_t board[BoardSize], int8_t col)
{
    int8_t newBoard[BoardSize];
    copy(board, board + BoardSize, newBoard);
    bool justPassed = false;
    int8_t moveInd;
    while (1)
    {
        moveInd = BoardSize - 1;
        if (!newMove(newBoard, col, rand() % BoardSize, moveInd))
            if (justPassed)
                break;
            else
                justPassed = true;
        else
            justPassed - false;
        col = -col;
    }
    return score(newBoard);
}