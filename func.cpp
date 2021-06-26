#include "func.h"
#include <vector>
#include <iostream>
using namespace std;

int vialeft(vector<vector<int>> &board, int col, int x, int y)
{
    //left
    if (y > 0)
    {
        int between = 0; //if here's stuff between new location and left location
        for (int i = y - 1; i >= 0; i--)
        {
            if (board[x][i] == 0)
                return 0;
            else if (board[x][i] == -col)
                between = 1;
            else if (board[x][i] == col)
                return between;
        }
    }
    return 0;
}
int viaright(vector<vector<int>> &board, int col, int x, int y)
{
    //right
    if (y < 7)
    {
        int between = 0; //if here's stuff between new location and left location
        for (int i = y + 1; i < 8; i++)
        {
            if (board[x][i] == 0)
                return 0;
            else if (board[x][i] == -col)
                between = 1;
            else if (board[x][i] == col)
                return between;
        }
    }
    return 0;
}
int viaup(vector<vector<int>> &board, int col, int x, int y)
{
    //up
    if (x > 0)
    {
        int between = 0; //if here's stuff between new location and left location
        for (int i = x - 1; i >= 0; i--)
        {
            if (board[i][y] == 0)
                return 0;
            else if (board[i][y] == -col)
                between = 1;
            else if (board[i][y] == col)
                return between;
        }
    }
    return 0;
}
int viadown(vector<vector<int>> &board, int col, int x, int y)
{
    //down
    if (x < 7)
    {
        int between = 0; //if here's stuff between new location and left location
        for (int i = x + 1; i < 8; i++)
        {
            if (board[i][y] == 0)
                return 0;
            else if (board[i][y] == -col)
                between = 1;
            else if (board[i][y] == col)
                return between;
        }
    }
    return 0;
}
int upright(vector<vector<int>> &board, int col, int x, int y)
{
    //up right
    if (x > 0 && y < 7)
    {
        int i = x;
        int j = y;
        int between = 0; //if here's stuff between new location and left location
        while (1)
        {
            i--;
            j++;
            if (i < 0 || j >= 8)
                break;
            else if (board[i][j] == 0)
                return 0;
            else if (board[i][j] == -col)
                between = 1;
            else if (board[i][j] == col)
                return between;
        }
    }
    return 0;
}
int upleft(vector<vector<int>> &board, int &col, int i, int j)
{
    //up left
    if (i > 0 && j > 0)
    {
        int between = 0; //if here's stuff between new location and left location
        while (1)
        {
            i--;
            j--;
            if (i < 0 || j < 0)
                break;
            else if (board[i][j] == 0)
                return 0;
            else if (board[i][j] == -col)
                between = 1;
            else if (board[i][j] == col)
                return between;
        }
    }
    return 0;
}
int downright(vector<vector<int>> &board, int &col, int i, int j)
{
    //down right
    if (i < 7 && j < 7)
    {
        int between = 0; //if here's stuff between new location and left location
        while (1)
        {
            i++;
            j++;
            if (i >= 8 || j >= 8)
                break;
            else if (board[i][j] == 0)
                return 0;
            else if (board[i][j] == -col)
                between = 1;
            else if (board[i][j] == col)
                return between;
        }
    }
    return 0;
}
int downleft(vector<vector<int>> &board, int &col, int i, int j)
{
    //down left
    if (i < 7 && j > 0)
    {
        int between = 0; //if here's stuff between new location and left location
        while (1)
        {
            i++;
            j--;
            if (i >= 8 || j < 0)
                break;
            else if (board[i][j] == 0)
                return 0;
            else if (board[i][j] == -col)
                between = 1;
            else if (board[i][j] == col)
                return between;
        }
    }
    return 0;
}
//if this is a viable move
int viable(vector<vector<int>> &board, int col, int i, int j)
{
    if (board[i][j] != 0)
        return 0;
    if (!vialeft(board, col, i, j))
    {
        if (!viaright(board, col, i, j))
        {
            if (!viaup(board, col, i, j))
            {
                if (!viadown(board, col, i, j))
                {
                    if (!upleft(board, col, i, j))
                    {
                        if (!upright(board, col, i, j))
                        {
                            if (!downleft(board, col, i, j))
                            {
                                if (!downright(board, col, i, j))
                                {
                                    return 0;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 1;
}

int puthere(vector<vector<int>> &board, int col, int x, int y)
{
    board[x][y] = col;
    if (vialeft(board, col, x, y))
    {
        for (int i = y - 1; i >= 0; i--)
        {
            if (board[x][i] == -col)
                board[x][i] = col;
            else if (board[x][i] == col)
                break;
        }
    }
    if (viaright(board, col, x, y))
    {
        for (int i = y + 1; i < 8; i++)
        {
            if (board[x][i] == -col)
                board[x][i] = col;
            else if (board[x][i] == col)
                break;
        }
    }
    if (viaup(board, col, x, y))
    {
        for (int i = x - 1; i >= 0; i--)
        {
            if (board[i][y] == -col)
                board[i][y] = col;
            else if (board[i][y] == col)
                break;
        }
    }
    if (viadown(board, col, x, y))
    {
        for (int i = x + 1; i < 8; i++)
        {
            if (board[i][y] == -col)
                board[i][y] = col;
            else if (board[i][y] == col)
                break;
        }
    }
    if (upright(board, col, x, y))
    {
        int i = x;
        int j = y;
        while (1)
        {
            i--;
            j++;
            if (i < 0 || j >= 8)
                break;
            else if (board[i][j] == -col)
                board[i][j] = col;
            else if (board[i][j] == col)
                break;
        }
    }
    if (upleft(board, col, x, y))
    {
        int i = x;
        int j = y;
        while (1)
        {
            i--;
            j--;
            if (i < 0 || j < 0)
                break;
            else if (board[i][j] == -col)
                board[i][j] = col;
            else if (board[i][j] == col)
                break;
        }
    }
    if (downright(board, col, x, y))
    {
        int i = x;
        int j = y;
        while (1)
        {
            i++;
            j++;
            if (i > 7 || j > 7)
                break;
            else if (board[i][j] == -col)
                board[i][j] = col;
            else if (board[i][j] == col)
                break;
        }
    }
    if (downleft(board, col, x, y))
    {
        int i = x;
        int j = y;
        while (1)
        {
            i++;
            j--;
            if (i >= 8 || j < 0)
                break;
            else if (board[i][j] == -col)
                board[i][j] = col;
            else if (board[i][j] == col)
                break;
        }
    }
    return 0;
}

//give list of coordinates, col of next step
void givelist(vector<vector<int>> &board, int col, vector<vector<int>> &ret)
{
    //returns a list of viable coordinates
    vector<int> matt{0, 0};
    ret.clear();
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (viable(board, col, i, j))
            {
                matt[0] = i;
                matt[1] = j;
                ret.push_back(matt);
            }
        }
    }
}

//print the board
int printboard(vector<vector<int>> &board)
{
    cout << "   0   1   2   3   4   5   6   7" << endl;
    for (int i = 0; i < board.size(); i++)
    {
        cout << char('A' + i) << "  ";
        for (int j = 0; j < board[i].size(); j++)
        {
            switch (board[i][j])
            {
            case 0:
                cout << ".   ";
                break;
            case 1:
                cout << "@   ";
                break;
            case -1:
                cout << "O   ";
                break;
            }
        }
        cout << endl
             << endl;
    }
    return 0;
}

//ret[0] = win color @ = 1 , O = -1
//ret[1] = game finished or not
vector<int> won(vector<vector<int>> &board)
{
    vector<int> ret;
    vector<vector<int>> choices;
    givelist(board, 1, choices);
    if (choices.size() == 0)
    {
        givelist(board, -1, choices);
        if (choices.size() == 0)
        {
            //no more moves
            int re = 0;
            for (int i = 0; i < 8; i++)
                for (int j = 0; j < 8; j++)
                    re += board[i][j];
            //re is the final count of their pieces
            if (re > 0)
                ret.push_back(1);
            else if (re < 0)
                ret.push_back(-1);
            else
                ret.push_back(0);
            ret.push_back(1);
            return ret;
        }
    }
    ret.push_back(0);
    ret.push_back(0);
    return ret;
}

//random choices return win or not, col of next step
int randomstep(vector<vector<int>> &board, int col)
{
    vector<vector<int>> cords;
    givelist(board, col, cords);
    //if not pass
    if (cords.size() != 0)
    {
        int ran = rand() % cords.size();
        int x = cords[ran][0];
        int y = cords[ran][1];
        puthere(board, col, x, y);
    }
    else
    {
        vector<int> win = won(board);
        if (win[1] != 0)
            return win[0];
    }
    return randomstep(board, -col);
}
