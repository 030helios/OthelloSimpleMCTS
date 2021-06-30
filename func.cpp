#include "func.h"
using namespace std;

int vialeft(array<int8_t, BoardSize> &board, int8_t &col, int i, int j)
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
int viaright(array<int8_t, BoardSize> &board, int8_t &col, int i, int j)
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
int viaup(array<int8_t, BoardSize> &board, int8_t &col, int i, int j)
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
int viadown(array<int8_t, BoardSize> &board, int8_t &col, int i, int j)
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

bool legal(array<int8_t, BoardSize> &board, int8_t &col, int i, int j)
{
    if (board[i * EdgeSize + j] != 0)
        return 0;
    if (i <= 1)
    {
        if (viadown(board, col, i, j))
            return 1;
        if (j <= 1)
        {
            if (viaright(board, col, i, j))
                return 1;
            if (downright(board, col, i, j))
                return 1;
        }
        else if (j >= EdgeSize - 2)
        {
            if (vialeft(board, col, i, j))
                return 1;
            if (downleft(board, col, i, j))
                return 1;
        }
        else
        {
            if (vialeft(board, col, i, j))
                return 1;
            if (downleft(board, col, i, j))
                return 1;
            if (viaright(board, col, i, j))
                return 1;
            if (downright(board, col, i, j))
                return 1;
        }
    }
    else if (i >= EdgeSize - 2)
    {
        if (viaup(board, col, i, j))
            return 1;
        if (j <= 1)
        {
            if (viaright(board, col, i, j))
                return 1;
            if (upright(board, col, i, j))
                return 1;
        }
        else if (j >= EdgeSize - 2)
        {
            if (vialeft(board, col, i, j))
                return 1;
            if (upleft(board, col, i, j))
                return 1;
        }
        else
        {
            if (vialeft(board, col, i, j))
                return 1;
            if (upleft(board, col, i, j))
                return 1;
            if (viaright(board, col, i, j))
                return 1;
            if (upright(board, col, i, j))
                return 1;
        }
    }
    else
    {
        if (vialeft(board, col, i, j))
            return 1;
        if (viaright(board, col, i, j))
            return 1;
        if (viaup(board, col, i, j))
            return 1;
        if (viadown(board, col, i, j))
            return 1;
        if (upleft(board, col, i, j))
            return 1;
        if (upright(board, col, i, j))
            return 1;
        if (downleft(board, col, i, j))
            return 1;
        if (downright(board, col, i, j))
            return 1;
    }
    return 0;
}
void playMoveAssumeLegal(array<int8_t, BoardSize> &board, int8_t &col, int x, int y)
{
    board[x * EdgeSize + y] = col;
    int dis = vialeft(board, col, x, y);
    for (int j = y - 1; j != y - 1 - dis; j--)
        board[x * EdgeSize + j] = col;
    dis = viaright(board, col, x, y);
    for (int j = y + 1; j != y + 1 + dis; j++)
        board[x * EdgeSize + j] = col;
    dis = viaup(board, col, x, y);
    for (int i = x - 1; i != x - 1 - dis; i--)
        board[i * EdgeSize + y] = col;
    dis = viadown(board, col, x, y);
    for (int i = x + 1; i != x + 1 + dis; i++)
        board[i * EdgeSize + y] = col;

    dis = upright(board, col, x, y);
    {
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
    {
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
    {
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
    {
        int i = x;
        int j = y;
        while (i != x + dis)
        {
            i++;
            j--;
            board[i * EdgeSize + j] = col;
        }
    }
}
//give list of coordinates, col of next step
void legalMoves(array<int8_t, BoardSize> &board, int8_t &col, array<pair<int8_t, int8_t>, 25> &ret, int8_t &haschild)
{
    for (int i = 0; i < EdgeSize; i++)
        for (int j = 0; j < EdgeSize; j++)
            if (legal(board, col, i, j))
            {
                ret[haschild].first = i;
                ret[haschild].second = j;
                haschild++;
            }
}

//print the board
void printboard(array<int8_t, BoardSize> board)
{
    string str = "./eyesore.py ";
    str += to_string(EdgeSize) + " ";
    for (int i = 0; i < BoardSize; i++)
    {
        str += to_string(board[i]);
        str += ".";
    }
    char exe[str.length()];
    strcpy(exe, str.c_str());
    system(exe);
}
//ret[0] = win color @ = 1 , O = -1
//ret[1] = game finished or not
vector<int> won(array<int8_t, BoardSize> &board)
{
    vector<int> ret{0, 0};
    array<pair<int8_t, int8_t>, 25> choices;
    int8_t haschild = 0;
    int8_t col = 1;
    legalMoves(board, col, choices, haschild);
    if (!haschild)
    {
        col = -1;
        legalMoves(board, col, choices, haschild);
        if (!haschild)
        {
            //no more moves
            int re = 0;
            for (int i = 0; i < EdgeSize; i++)
                for (int j = 0; j < EdgeSize; j++)
                    re += board[i * EdgeSize + j];
            //re is the final count of their pieces
            if (re > 0)
                ret[0] = 1;
            else if (re < 0)
                ret[0] = -1;
            ret[1] = 1;
            return ret;
        }
    }
    return ret;
}