#include "func.h"
using namespace std;

int toleft(array<int8_t, BoardSize> &board, int8_t &col, int i, int j)
{
    if (j > 1)
    {
        int between = 0; //if here's stuff between new location and left location
        for (j--; j >= 0; j--)
        {
            if (board[i * EdgeSize + j] == 0)
                return 0;
            else if (board[i * EdgeSize + j] == -col)
                between++;
            else if (board[i * EdgeSize + j] == col)
                return between;
        }
    }
    return 0;
}
int toright(array<int8_t, BoardSize> &board, int8_t &col, int i, int j)
{
    if (j < (EdgeSize - 2))
    {
        int between = 0; //if here's stuff between new location and left location
        for (j++; j < EdgeSize; j++)
        {
            if (board[i * EdgeSize + j] == 0)
                return 0;
            else if (board[i * EdgeSize + j] == -col)
                between++;
            else if (board[i * EdgeSize + j] == col)
                return between;
        }
    }
    return 0;
}
int toup(array<int8_t, BoardSize> &board, int8_t &col, int i, int j)
{
    if (i > 1)
    {
        int between = 0; //if here's stuff between new location and left location
        for (i--; i >= 0; i--)
        {
            if (board[i * EdgeSize + j] == 0)
                return 0;
            else if (board[i * EdgeSize + j] == -col)
                between++;
            else if (board[i * EdgeSize + j] == col)
                return between;
        }
    }
    return 0;
}
int todown(array<int8_t, BoardSize> &board, int8_t &col, int i, int j)
{
    if (i < (EdgeSize - 2))
    {
        int between = 0; //if here's stuff between new location and left location
        for (i++; i < EdgeSize; i++)
        {
            if (board[i * EdgeSize + j] == 0)
                return 0;
            else if (board[i * EdgeSize + j] == -col)
                between++;
            else if (board[i * EdgeSize + j] == col)
                return between;
        }
    }
    return 0;
}
int upright(array<int8_t, BoardSize> &board, int8_t &col, int i, int j)
{
    if (i > 1 && j < (EdgeSize - 2))
    {
        int between = 0; //if here's stuff between new location and left location
        while (i > 0 && j < (EdgeSize - 1))
        {
            i--;
            j++;
            if (board[i * EdgeSize + j] == 0)
                return 0;
            else if (board[i * EdgeSize + j] == -col)
                between++;
            else if (board[i * EdgeSize + j] == col)
                return between;
        }
    }
    return 0;
}
int upleft(array<int8_t, BoardSize> &board, int8_t &col, int i, int j)
{
    if (i > 1 && j > 1)
    {
        int between = 0; //if here's stuff between new location and left location
        while (i > 0 && j > 0)
        {
            i--;
            j--;
            if (board[i * EdgeSize + j] == 0)
                return 0;
            else if (board[i * EdgeSize + j] == -col)
                between++;
            else if (board[i * EdgeSize + j] == col)
                return between;
        }
    }
    return 0;
}
int downright(array<int8_t, BoardSize> &board, int8_t &col, int i, int j)
{
    if (i < (EdgeSize - 2) && j < (EdgeSize - 2))
    {
        int between = 0; //if here's stuff between new location and left location
        while (i < (EdgeSize - 1) && j < (EdgeSize - 1))
        {
            i++;
            j++;
            if (board[i * EdgeSize + j] == 0)
                return 0;
            else if (board[i * EdgeSize + j] == -col)
                between++;
            else if (board[i * EdgeSize + j] == col)
                return between;
        }
    }
    return 0;
}
int downleft(array<int8_t, BoardSize> &board, int8_t &col, int i, int j)
{
    if (i < (EdgeSize - 2) && j > 1)
    {
        int between = 0; //if here's stuff between new location and left location
        while (i < (EdgeSize - 1) && j > 0)
        {
            i++;
            j--;
            if (board[i * EdgeSize + j] == 0)
                return 0;
            else if (board[i * EdgeSize + j] == -col)
                between++;
            else if (board[i * EdgeSize + j] == col)
                return between;
        }
    }
    return 0;
}

bool tryMove(array<int8_t, BoardSize> &board, int8_t &col, int x, int y)
{
    if (board[x * EdgeSize + y] != 0)
        return false;
    bool touched = false;
    int dis = toleft(board, col, x, y);
    if (dis)
    {
        touched = true;
        for (int j = y - 1; j != y - 1 - dis; j--)
            board[x * EdgeSize + j] = col;
    }
    dis = toright(board, col, x, y);
    if (dis)
    {
        touched = true;
        for (int j = y + 1; j != y + 1 + dis; j++)
            board[x * EdgeSize + j] = col;
    }
    dis = toup(board, col, x, y);
    if (dis)
    {
        touched = true;
        for (int i = x - 1; i != x - 1 - dis; i--)
            board[i * EdgeSize + y] = col;
    }
    dis = todown(board, col, x, y);
    if (dis)
    {
        touched = true;
        for (int i = x + 1; i != x + 1 + dis; i++)
            board[i * EdgeSize + y] = col;
    }
    dis = upright(board, col, x, y);
    if (dis)
    {
        touched = true;
        int i = x;
        int j = y;
        while (i != x - dis)
        {
            i--;
            j++;
            board[i * EdgeSize + j] = col;
        }
    }
    dis = upleft(board, col, x, y);
    if (dis)
    {
        touched = true;
        int i = x;
        int j = y;
        while (i != x - dis)
        {
            i--;
            j--;
            board[i * EdgeSize + j] = col;
        }
    }
    dis = downright(board, col, x, y);
    if (dis)
    {
        touched = true;
        int i = x;
        int j = y;
        while (i != x + dis)
        {
            i++;
            j++;
            board[i * EdgeSize + j] = col;
        }
    }
    dis = downleft(board, col, x, y);
    if (dis)
    {
        touched = true;
        int i = x;
        int j = y;
        while (i != x + dis)
        {
            i++;
            j--;
            board[i * EdgeSize + j] = col;
        }
    }
    if (touched)
        board[x * EdgeSize + y] = col;
    return touched;
}
//return true if we made a move
bool newMove(array<int8_t, BoardSize> &board, int8_t &col, int8_t &RdId, int8_t &moveIndex)
{
    array<pair<int8_t, int8_t>, BoardSize> &MoveArr = RdMoves[RdId];
    while (!tryMove(board, col, MoveArr[moveIndex].first, MoveArr[moveIndex].second))
        if (--moveIndex < 0)
            return false;
    moveIndex--;
    return true;
}
void printboard(array<int8_t, BoardSize> board, string name)
{
    string str = "./Storage/eyesore.py " + to_string(EdgeSize) + " " + name + " ";
    for (int stone : board)
        str += to_string(stone) + ".";
    char exe[str.length()];
    strcpy(exe, str.c_str());
    system(exe);
}
bool hasMove(array<int8_t, BoardSize> board, int8_t col)
{
    int8_t moveIndex = BoardSize - 1, zero = 0;
    return newMove(board, col, zero, moveIndex);
}
//ret[0] = win color @ = 1 , O = -1
//ret[1] = game finished or not
vector<int> won(array<int8_t, BoardSize> &board)
{
    vector<int> ret{0, 0};
    if (!hasMove(board, 1))
        if (!hasMove(board, -1))
        {
            ret[1] = 1;
            for (auto stone : board)
                ret[0] += stone;
            ret[0] = (ret[0] > 0) - (ret[0] < 0);
        }
    return ret;
}