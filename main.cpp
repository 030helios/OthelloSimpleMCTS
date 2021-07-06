#include "func.h"
#include "node.h"
#include <chrono>
#include <thread>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
using namespace chrono;

// Default heat value for root exploration.
// Depends on clock rate, thinkTime and threadCount. Which leaves room for improvement.
float depth;

//continue exploring until time up
void Countdown(system_clock::time_point start, milliseconds thinkTime, Node *root, int threadcount)
{
    milliseconds timepast = duration_cast<milliseconds>(system_clock::now() - start);
    while (timepast < thinkTime)
    {
        root->explore(round(depth - log(timepast.count() * threadcount) / log(EdgeSize)));
        timepast = duration_cast<milliseconds>(system_clock::now() - start);
    }
}

array<int8_t, BoardSize> GetStep(array<int8_t, BoardSize> board, int &thinkTime, int threadCount, Node *&root)
{
    root = root->playermove(board);
    root->clean();
    //initialize thread
    vector<thread> threadvec;
    for (int i = 0; i < threadCount; i++)
        threadvec.emplace_back(Countdown, system_clock::now(), seconds(thinkTime), root, threadCount);
    for (int i = 0; i < threadCount; i++)
        threadvec[i].join();

    cout << "Total playouts: " << root->totalgames << endl;
    if (root->gameover == -2 || root->gameover == 0)
    {
        if (root->gameover == 0)
            cout << "Maybe Draw\n";
        cout << (root->col == 1 ? "Black " : "White ");
        root = root->getbest();
        float childUtility = float(root->totalScore * root->col) / (2 * root->totalgames);
        cout << "winrate estimate: " << 0.5 - childUtility << endl;
        return root->board;
    }
    else
    {
        thinkTime = 0;
        cout << "Winner: " << (root->gameover == 1 ? "Black\n" : "White\n");
    }
    root = root->getbest();
    return root->board;
}
//An array of shuffled arrays filled with indexes
array<array<pair<int8_t, int8_t>, BoardSize>, BoardSize> shuffledMoves;
void init(array<int8_t, BoardSize> &board)
{
    int d = EdgeSize / 2 + EdgeSize * EdgeSize / 2;
    board[d] = 1;
    board[d - 1] = -1;
    board[d - EdgeSize] = -1;
    board[d - EdgeSize - 1] = 1;
    srand(system_clock::to_time_t(system_clock::now()));
    array<pair<int8_t, int8_t>, BoardSize> defaultMoves;
    for (int i = 0; i < EdgeSize; i++)
        for (int j = 0; j < EdgeSize; j++)
            defaultMoves[i * EdgeSize + j] = make_pair(i, j);
    for (auto &moves : shuffledMoves)
        moves = defaultMoves;
    for (auto &moves : shuffledMoves)
        random_shuffle(moves.begin(), moves.end());
}

int main()
{
    //default black
    int computerColor = 1;
    int timeLimit, threadCount;
    cout << "TimeLimit :";
    cin >> timeLimit;
    cout << "ThreadCount :";
    cin >> threadCount;

    depth = log(timeLimit * 1000 * threadCount) / log(EdgeSize) + 0.5;

    array<int8_t, BoardSize> board{};
    init(board);

    Node Source(board, computerColor);
    Node *root = &Source;
    string ImgName = "Output_";
    int index = 0;
    while (hasMove(board, 1) || hasMove(board, -1))
    {
        cout << "Round " << index << endl;
        printboard(board, ImgName + to_string(index++));
        board = GetStep(board, timeLimit, threadCount, root);
    }
    printboard(board, ImgName + to_string(index++));
    cout << "Winner: " << (score(board) == 1 ? "Black" : "White") << endl;
    return 0;
}