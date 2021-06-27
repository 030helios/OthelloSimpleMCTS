#include "func.h"
#include <vector>
#include <iostream>
using namespace std;

int vialeft(vector<vector<int>> &board, int col, int i, int j)
{
    if (j > 1)
    {
        int between = 0; //if here's stuff between new location and left location
        for (j--; j >= 0; j--)
        {
            if (board[i][j] == 0)
                return 0;
            else if (board[i][j] == -col)
                between++;
            else if (board[i][j] == col)
                return between;
        }
    }
    return 0;
}
int viaright(vector<vector<int>> &board, int col, int i, int j)
{
    if (j < 6)
    {
        int between = 0; //if here's stuff between new location and left location
        for (j++; j < 8; j++)
        {
            if (board[i][j] == 0)
                return 0;
            else if (board[i][j] == -col)
                between++;
            else if (board[i][j] == col)
                return between;
        }
    }
    return 0;
}
int viaup(vector<vector<int>> &board, int col, int i, int j)
{
    if (i > 1)
    {
        int between = 0; //if here's stuff between new location and left location
        for (i--; i >= 0; i--)
        {
            if (board[i][j] == 0)
                return 0;
            else if (board[i][j] == -col)
                between++;
            else if (board[i][j] == col)
                return between;
        }
    }
    return 0;
}
int viadown(vector<vector<int>> &board, int col, int i, int j)
{
    if (i < 6)
    {
        int between = 0; //if here's stuff between new location and left location
        for (i++; i < 8; i++)
        {
            if (board[i][j] == 0)
                return 0;
            else if (board[i][j] == -col)
                between++;
            else if (board[i][j] == col)
                return between;
        }
    }
    return 0;
}
int upright(vector<vector<int>> &board, int col, int i, int j)
{
    if (i > 1 && j < 6)
    {
        int between = 0; //if here's stuff between new location and left location
        while (i > 0 && j < 7)
        {
            i--;
            j++;
            if (board[i][j] == 0)
                return 0;
            else if (board[i][j] == -col)
                between++;
            else if (board[i][j] == col)
                return between;
        }
    }
    return 0;
}
int upleft(vector<vector<int>> &board, int &col, int i, int j)
{
    if (i > 1 && j > 1)
    {
        int between = 0; //if here's stuff between new location and left location
        while (i > 0 && j > 0)
        {
            i--;
            j--;
            if (board[i][j] == 0)
                return 0;
            else if (board[i][j] == -col)
                between++;
            else if (board[i][j] == col)
                return between;
        }
    }
    return 0;
}
int downright(vector<vector<int>> &board, int &col, int i, int j)
{
    if (i < 6 && j < 6)
    {
        int between = 0; //if here's stuff between new location and left location
        while (i < 7 && j < 7)
        {
            i++;
            j++;
            if (board[i][j] == 0)
                return 0;
            else if (board[i][j] == -col)
                between++;
            else if (board[i][j] == col)
                return between;
        }
    }
    return 0;
}
int downleft(vector<vector<int>> &board, int &col, int i, int j)
{
    if (i < 6 && j > 1)
    {
        int between = 0; //if here's stuff between new location and left location
        while (i < 7 && j > 0)
        {
            i++;
            j--;
            if (board[i][j] == 0)
                return 0;
            else if (board[i][j] == -col)
                between++;
            else if (board[i][j] == col)
                return between;
        }
    }
    return 0;
}
bool legal(vector<vector<int>> &board, int col, int i, int j)
{
    if (board[i][j] != 0)
        return 0;
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
    return 0;
}

void playMoveAssumeLegal(vector<vector<int>> &board, int col, int x, int y)
{
    board[x][y] = col;
    int dis = vialeft(board, col, x, y);
    for (int j = y - 1; j != y - 1 - dis; j--)
        board[x][j] = col;
    dis = viaright(board, col, x, y);
    for (int j = y + 1; j != y + 1 + dis; j++)
        board[x][j] = col;
    dis = viaup(board, col, x, y);
    for (int i = x - 1; i != x - 1 - dis; i--)
        board[i][y] = col;
    dis = viadown(board, col, x, y);
    for (int i = x + 1; i != x + 1 + dis; i++)
        board[i][y] = col;

    dis = upright(board, col, x, y);
    {
        int i = x;
        int j = y;
        while (i != x - dis)
        {
            i--;
            j++;
            board[i][j] = col;
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
            board[i][j] = col;
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
            board[i][j] = col;
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
            board[i][j] = col;
        }
    }
}

//give list of coordinates, col of next step
void legalMoves(vector<vector<int>> &board, int col, vector<vector<int>> &ret)
{
    vector<int> matt{0, 0};
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (legal(board, col, i, j))
            {
                matt[0] = i;
                matt[1] = j;
                ret.push_back(matt);
            }
}

//print the board
void printboard(vector<vector<int>> &board)
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
        cout << "\n\n";
    }
}

//ret[0] = win color @ = 1 , O = -1
//ret[1] = game finished or not
vector<int> won(vector<vector<int>> &board)
{
    vector<int> ret{0, 0};
    vector<vector<int>> choices;
    legalMoves(board, 1, choices);
    if (choices.size() == 0)
    {
        legalMoves(board, -1, choices);
        if (choices.size() == 0)
        {
            //no more moves
            int re = 0;
            for (int i = 0; i < 8; i++)
                for (int j = 0; j < 8; j++)
                    re += board[i][j];
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
//random choices return win or not, col of next step
int playout(vector<vector<int>> board, int col)
{
    vector<vector<int>> moves;
    while (1)
    {
        moves.clear();
        legalMoves(board, col, moves);
        //if not pass
        if (moves.size())
        {
            int ran = rand() % moves.size();
            playMoveAssumeLegal(board, col, moves[ran][0], moves[ran][1]);
        }
        else
        {
            vector<int> win = won(board);
            if (win[1] != 0)
                return win[0];
        }
        col = -col;
    }
}