#include "func.h"
#include "node.h"
#include "bot.h"
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
using namespace chrono;

//calls /Storage/eyesore.py
void printboard(int8_t board[BoardSize], string name)
{
    string str = "./Storage/eyesore.py " + to_string(EdgeSize) + " " + name + ".jpg ";
    for (int i = 0; i < BoardSize; i++)
        str += to_string(board[i]) + ".";
    char exe[str.length()];
    strcpy(exe, str.c_str());
    system(exe);
}
//An array of shuffled arrays filled with indexes
int8_t Ishuffled[BoardSize * BoardSize];
int8_t Jshuffled[BoardSize * BoardSize];

int main()
{
    int timeLimit, threadCount;
    cout << "TimeLimit :";
    cin >> timeLimit;
    cout << "ThreadCount :";
    cin >> threadCount;

    srand(system_clock::to_time_t(system_clock::now()));

    array<pair<int8_t, int8_t>, BoardSize> moves;
    for (int i = 0; i < EdgeSize; i++)
        for (int j = 0; j < EdgeSize; j++)
            moves[i * EdgeSize + j] = make_pair(i, j);

    for (int ind = 0; ind < BoardSize; ind++)
    {
        random_shuffle(moves.begin(), moves.end());
        for (int i = 0; i < BoardSize; i++)
        {
            Ishuffled[ind * BoardSize + i] = moves[i].first;
            Jshuffled[ind * BoardSize + i] = moves[i].second;
        }
    }

    int8_t sourceBoard[BoardSize] = {0};
    int8_t *board = sourceBoard;
    int d = EdgeSize / 2 + EdgeSize * EdgeSize / 2;
    board[d] = 1;
    board[d - 1] = -1;
    board[d - EdgeSize] = -1;
    board[d - EdgeSize - 1] = 1;
    //default black
    Bot bot(timeLimit, threadCount, board, 1);

    int index = 0;
    string ImgName = "Output_";
    vector<thread> threadVec;
    threadVec.emplace_back(printboard, board, ImgName + to_string(index));
    while (hasMove(board, 1) || hasMove(board, -1))
    {
        cout << "Round " << index << endl;
        board = bot.play(board);
        threadVec.emplace_back(printboard, board, ImgName + to_string(++index));
    }
    for (auto &thr : threadVec)
        thr.join();
    cout << "Winner: " << (score(board) == 1 ? "Black" : "White") << endl;
    return 0;
}