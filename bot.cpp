#include "bot.h"
#include <iostream>

Bot::~Bot(){
    for(auto &thd:threadVec)
        thd.join();
}
Bot::Bot(int timeLimit, int threadCount, array<int8_t, BoardSize> board, int8_t color)
{
    this->timeLimit = timeLimit;
    this->threadCount = threadCount;
    depth = log(timeLimit * 1000 * threadCount) / log(EdgeSize) + 0.5;
    source = Node(board, color);
    root = &source;
}
//removes any child that isn't keep
void Bot::trim(Node *parent, Node *keep)
{
    while (&parent->children.front() != keep)
        parent->children.pop_front();
    while (&parent->children.back() != keep)
        parent->children.pop_back();
}
void Bot::countdown(system_clock::time_point start, milliseconds thinkTime, Node *root, float depth, int threadCount)
{
    milliseconds timepast = duration_cast<milliseconds>(system_clock::now() - start);
    while (timepast < thinkTime)
    {
        root->explore(round(depth - log(timepast.count() * threadCount) / log(EdgeSize)));
        timepast = duration_cast<milliseconds>(system_clock::now() - start);
    }
}
//makes a play and returns the board
array<int8_t, BoardSize> Bot::play(array<int8_t, BoardSize> board)
{
    system_clock::time_point start = system_clock::now();
    enemyMove(board);
    root->clean();
    vector<thread> jobs;
    for (int i = 0; i < threadCount; i++)
        jobs.emplace_back(countdown, start, seconds(timeLimit), root, depth, threadCount);
    for (int i = 0; i < threadCount; i++)
        jobs[i].join();

    cout << "Total playouts: " << root->totalGames << endl;
    if (root->gameover == -2 || root->gameover == 0)
    {
        if (root->gameover == 0)
            cout << "Maybe Draw, ";
        cout << (root->col == 1 ? "Black " : "White ");
        float winrate = 0.5 + float(root->totalScore * root->col) / (2 * root->totalGames);
        cout << "winrate estimate: " << winrate << endl;
    }
    else
        cout << "Winner: " << (root->gameover == 1 ? "Black\n" : "White\n");
    move();
    return root->board;
}
//updates root to the most visited child node
void Bot::move()
{
    Node *best = &root->children.front();
    for (auto &child : root->children)
        if (child.totalGames > best->totalGames)
            best = &child;
    for (auto &child : root->children)
        if (child.gameover == root->col)
            best = &child;
    threadVec.emplace_back(trim, root, best);
    root = best;
}
//changes root if there's a child with such board
void Bot::enemyMove(array<int8_t, BoardSize> &target)
{
    Node *nextRoot = nullptr;
    for (auto &child : root->children)
        if (child.board == target)
            nextRoot = &child;
    if (nextRoot)
    {
        threadVec.emplace_back(trim, root, nextRoot);
        root = nextRoot;
    }
}