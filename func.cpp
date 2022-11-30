#include "func.h"
#include <numeric>
#include <algorithm>
using namespace std;

void tryleft(int8_t board[BoardSize], int8_t color, int8_t i, int8_t j, bool &legal)
{
    int flip = 0; // the amount of stones we flip
    while (--j >= 0)
        if (board[i * EdgeSize + j] == 0)
            return;
        else if (board[i * EdgeSize + j] == color)
        {
            if (flip)
                legal = true;
            while (flip--)
                board[i * EdgeSize + ++j] = color;
            return;
        }
        else
            flip++;
}
void tryright(int8_t board[BoardSize], int8_t color, int8_t i, int8_t j, bool &legal)
{
    int flip = 0; // the amount of stones we flip
    while (++j < EdgeSize)
        if (board[i * EdgeSize + j] == 0)
            return;
        else if (board[i * EdgeSize + j] == color)
        {
            if (flip)
                legal = true;
            while (flip--)
                board[i * EdgeSize + --j] = color;
            return;
        }
        else
            flip++;
}
void tryup(int8_t board[BoardSize], int8_t color, int8_t i, int8_t j, bool &legal)
{
    int flip = 0; // the amount of stones we flip
    while (--i >= 0)
        if (board[i * EdgeSize + j] == 0)
            return;
        else if (board[i * EdgeSize + j] == color)
        {
            if (flip)
                legal = true;
            while (flip--)
                board[++i * EdgeSize + j] = color;
            return;
        }
        else
            flip++;
}
void trydown(int8_t board[BoardSize], int8_t color, int8_t i, int8_t j, bool &legal)
{
    int flip = 0; // the amount of stones we flip
    while (++i < EdgeSize)
        if (board[i * EdgeSize + j] == 0)
            return;
        else if (board[i * EdgeSize + j] == color)
        {
            if (flip)
                legal = true;
            while (flip--)
                board[--i * EdgeSize + j] = color;
            return;
        }
        else
            flip++;
}
void upright(int8_t board[BoardSize], int8_t color, int8_t i, int8_t j, bool &legal)
{
    int flip = 0; // the amount of stones we flip
    while (--i >= 0 && ++j < EdgeSize)
        if (board[i * EdgeSize + j] == 0)
            return;
        else if (board[i * EdgeSize + j] == color)
        {
            if (flip)
                legal = true;
            while (flip--)
                board[++i * EdgeSize + --j] = color;
            return;
        }
        else
            flip++;
}
void upleft(int8_t board[BoardSize], int8_t color, int8_t i, int8_t j, bool &legal)
{
    int flip = 0; // the amount of stones we flip
    while (--i >= 0 && --j >= 0)
        if (board[i * EdgeSize + j] == 0)
            return;
        else if (board[i * EdgeSize + j] == color)
        {
            if (flip)
                legal = true;
            while (flip--)
                board[++i * EdgeSize + ++j] = color;
            return;
        }
        else
            flip++;
}
void downright(int8_t board[BoardSize], int8_t color, int8_t i, int8_t j, bool &legal)
{
    int flip = 0; // the amount of stones we flip
    while (++i < EdgeSize && ++j < EdgeSize)
        if (board[i * EdgeSize + j] == 0)
            return;
        else if (board[i * EdgeSize + j] == color)
        {
            if (flip)
                legal = true;
            while (flip--)
                board[--i * EdgeSize + --j] = color;
            return;
        }
        else
            flip++;
}
void downleft(int8_t board[BoardSize], int8_t color, int8_t i, int8_t j, bool &legal)
{
    int flip = 0; // the amount of stones we flip
    while (++i < EdgeSize && --j >= 0)
        if (board[i * EdgeSize + j] == 0)
            return;
        else if (board[i * EdgeSize + j] == color)
        {
            if (flip)
                legal = true;
            while (flip--)
                board[--i * EdgeSize + ++j] = color;
            return;
        }
        else
            flip++;
}
// Attempts a move on the position i,j. Returns true and changes the board if such move is legal.
bool tryMove(int8_t board[BoardSize], int8_t color, int8_t i, int8_t j)
{
    if (board[i * EdgeSize + j] != 0)
        return false;
    bool legal = false;
    if (j > 1)
        tryleft(board, color, i, j, legal);
    if (j < (EdgeSize - 2))
        tryright(board, color, i, j, legal);
    if (i > 1)
        tryup(board, color, i, j, legal);
    if (i < (EdgeSize - 2))
        trydown(board, color, i, j, legal);
    if (i > 1 && j < (EdgeSize - 2))
        upright(board, color, i, j, legal);
    if (i > 1 && j > 1)
        upleft(board, color, i, j, legal);
    if (i < (EdgeSize - 2) && j < (EdgeSize - 2))
        downright(board, color, i, j, legal);
    if (i < (EdgeSize - 2) && j > 1)
        downleft(board, color, i, j, legal);
    if (legal)
        board[i * EdgeSize + j] = color;
    return legal;
}
// Returns true if we made a move
bool newMove(int8_t board[BoardSize], int8_t color, int8_t shuffleID, int8_t &moveIndex)
{
    int8_t *I = &Ishuffled[shuffleID * BoardSize];
    int8_t *J = &Jshuffled[shuffleID * BoardSize];
    while (!tryMove(board, color, I[moveIndex], J[moveIndex]))
        if (--moveIndex < 0)
            return false;
    moveIndex--;
    return true;
}
bool hasMove(int8_t board[BoardSize], int8_t color)
{
    int8_t newBoard[BoardSize];
    copy(board, board + BoardSize, newBoard);
    int8_t moveIndex = BoardSize - 1;
    return newMove(newBoard, color, 0, moveIndex);
}
int score(int8_t board[BoardSize])
{
    int ret = accumulate(board, board + BoardSize, 0);
    return (ret > 0) - (ret < 0);
}
// Makes random moves, returns the outcome of the game
int playout(int8_t board[BoardSize], int8_t color)
{
    int8_t newBoard[BoardSize];
    copy(board, board + BoardSize, newBoard);
    bool justPassed = false;
    int8_t moveInd;
    while (1)
    {
        moveInd = BoardSize - 1;
        if (!newMove(newBoard, color, rand() % randomness, moveInd))
            if (justPassed)
                break;
            else
                justPassed = true;
        else
            justPassed - false;
        color = -color;
    }
    return score(newBoard);
}