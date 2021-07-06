#include "func.h"
using namespace std;

void tryleft(array<int8_t, BoardSize> &board, int8_t col, int8_t i, int8_t j, bool &legal)
{
    if (j <= 1)
        return;
    int flip = 0; //the amount of stones we flip
    for (j--; j >= 0; j--)
        if (board[i * EdgeSize + j] == 0)
            return;
        else if (board[i * EdgeSize + j] == -col)
            flip++;
        else if (board[i * EdgeSize + j] == col)
        {
            if (flip)
                legal = true;
            while (flip--)
                board[i * EdgeSize + ++j] = col;
            return;
        }
}
void tryright(array<int8_t, BoardSize> &board, int8_t col, int8_t i, int8_t j, bool &legal)
{
    if (j >= (EdgeSize - 2))
        return;
    int flip = 0; //the amount of stones we flip
    for (j++; j < EdgeSize; j++)
        if (board[i * EdgeSize + j] == 0)
            return;
        else if (board[i * EdgeSize + j] == -col)
            flip++;
        else if (board[i * EdgeSize + j] == col)
        {
            if (flip)
                legal = true;
            while (flip--)
                board[i * EdgeSize + --j] = col;
            return;
        }
}
void tryup(array<int8_t, BoardSize> &board, int8_t col, int8_t i, int8_t j, bool &legal)
{
    if (i <= 1)
        return;
    int flip = 0; //the amount of stones we flip
    for (i--; i >= 0; i--)
        if (board[i * EdgeSize + j] == 0)
            return;
        else if (board[i * EdgeSize + j] == -col)
            flip++;
        else if (board[i * EdgeSize + j] == col)
        {
            if (flip)
                legal = true;
            while (flip--)
                board[++i * EdgeSize + j] = col;
            return;
        }
}
void trydown(array<int8_t, BoardSize> &board, int8_t col, int8_t i, int8_t j, bool &legal)
{
    if (i >= (EdgeSize - 2))
        return;
    int flip = 0; //the amount of stones we flip
    for (i++; i < EdgeSize; i++)
        if (board[i * EdgeSize + j] == 0)
            return;
        else if (board[i * EdgeSize + j] == -col)
            flip++;
        else if (board[i * EdgeSize + j] == col)
        {
            if (flip)
                legal = true;
            while (flip--)
                board[--i * EdgeSize + j] = col;
            return;
        }
}
void upright(array<int8_t, BoardSize> &board, int8_t col, int8_t i, int8_t j, bool &legal)
{
    if (i <= 1 || j >= (EdgeSize - 2))
        return;
    int flip = 0; //the amount of stones we flip
    while (i-- > 0 && j++ < (EdgeSize - 1))
        if (board[i * EdgeSize + j] == 0)
            return;
        else if (board[i * EdgeSize + j] == -col)
            flip++;
        else if (board[i * EdgeSize + j] == col)
        {
            if (flip)
                legal = true;
            while (flip--)
                board[++i * EdgeSize + --j] = col;
            return;
        }
}
void upleft(array<int8_t, BoardSize> &board, int8_t col, int8_t i, int8_t j, bool &legal)
{
    if (i <= 1 || j <= 1)
        return;
    int flip = 0; //the amount of stones we flip
    while (i-- > 0 && j-- > 0)
        if (board[i * EdgeSize + j] == 0)
            return;
        else if (board[i * EdgeSize + j] == -col)
            flip++;
        else if (board[i * EdgeSize + j] == col)
        {
            if (flip)
                legal = true;
            while (flip--)
                board[++i * EdgeSize + ++j] = col;
            return;
        }
}
void downright(array<int8_t, BoardSize> &board, int8_t col, int8_t i, int8_t j, bool &legal)
{
    if (i >= (EdgeSize - 2) || j >= (EdgeSize - 2))
        return;
    int flip = 0; //the amount of stones we flip
    while (i++ < (EdgeSize - 1) && j++ < (EdgeSize - 1))
        if (board[i * EdgeSize + j] == 0)
            return;
        else if (board[i * EdgeSize + j] == -col)
            flip++;
        else if (board[i * EdgeSize + j] == col)
        {
            if (flip)
                legal = true;
            while (flip--)
                board[--i * EdgeSize + --j] = col;
            return;
        }
}
void downleft(array<int8_t, BoardSize> &board, int8_t col, int8_t i, int8_t j, bool &legal)
{
    if (i >= (EdgeSize - 2) || j <= 1)
        return;
    int flip = 0; //the amount of stones we flip
    while (i++ < (EdgeSize - 1) && j-- > 0)
        if (board[i * EdgeSize + j] == 0)
            return;
        else if (board[i * EdgeSize + j] == -col)
            flip++;
        else if (board[i * EdgeSize + j] == col)
        {
            if (flip)
                legal = true;
            while (flip--)
                board[--i * EdgeSize + ++j] = col;
            return;
        }
}
//Attempts a move on the position i,j. Returns true and changes the board if such move is legal.
bool tryMove(array<int8_t, BoardSize> &board, int8_t col, int8_t i, int8_t j)
{
    if (board[i * EdgeSize + j] != 0)
        return false;
    bool legal = false;
    tryleft(board, col, i, j, legal);
    tryright(board, col, i, j, legal);
    tryup(board, col, i, j, legal);
    trydown(board, col, i, j, legal);
    upright(board, col, i, j, legal);
    upleft(board, col, i, j, legal);
    downright(board, col, i, j, legal);
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
//Saves the board in /Storage
void printboard(array<int8_t, BoardSize> board, string name)
{
    string str = "./Storage/eyesore.py " + to_string(EdgeSize) + " " + name + ".jpg ";
    for (int stone : board)
        str += to_string(stone) + ".";
    char exe[str.length()];
    strcpy(exe, str.c_str());
    system(exe);
}
bool hasMove(array<int8_t, BoardSize> board, int8_t col)
{
    int8_t moveIndex = BoardSize - 1;
    return newMove(board, col, 0, moveIndex);
}