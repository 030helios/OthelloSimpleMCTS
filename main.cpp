#include "func.h"
#include "node.h"
#include "bot.h"
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
using namespace chrono;

//calls /Storage/eyesore.py
void printboard(array<int8_t, BoardSize> board, string name)
{
    string str = "./Storage/eyesore.py " + to_string(EdgeSize) + " " + name + ".jpg ";
    for (int stone : board)
        str += to_string(stone) + ".";
    char exe[str.length()];
    strcpy(exe, str.c_str());
    system(exe);
}
//An array of shuffled arrays filled with indexes
array<array<pair<int8_t, int8_t>, BoardSize>, BoardSize> shuffledMoves;
int main()
{
    int timeLimit, threadCount;
    cout << "TimeLimit :";
    cin >> timeLimit;
    cout << "ThreadCount :";
    cin >> threadCount;

    srand(system_clock::to_time_t(system_clock::now()));
    for (auto &moves : shuffledMoves)
    {
        for (int i = 0; i < EdgeSize; i++)
            for (int j = 0; j < EdgeSize; j++)
                moves[i * EdgeSize + j] = make_pair(i, j);
        random_shuffle(moves.begin(), moves.end());
    }

    array<int8_t, BoardSize> board{};
    int d = EdgeSize / 2 + EdgeSize * EdgeSize / 2;
    board[d] = 1;
    board[d - 1] = -1;
    board[d - EdgeSize] = -1;
    board[d - EdgeSize - 1] = 1;
    //default black
    Bot bot(timeLimit, threadCount, board, 1);

    int index = 0;
    string ImgName = "Output_";
    printboard(board, ImgName + to_string(index));
    while (hasMove(board, 1) || hasMove(board, -1))
    {
        cout << "Round " << index << endl;
        board = bot.play(board);
        printboard(board, ImgName + to_string(++index));
    }
    cout << "Winner: " << (score(board) == 1 ? "Black" : "White") << endl;
    return 0;
}