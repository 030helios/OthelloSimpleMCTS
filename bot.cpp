#include "bot.h"
#include <iostream>
#include <algorithm>

Bot::~Bot()
{
    for (auto &thd : threadVec)
        thd.join();
}
Bot::Bot(int tLimit, int thrCount, int8_t board[BoardSize], int8_t color) : timeLimit(seconds(tLimit)), threadCount(thrCount)
{
    depth = log(timeLimit.count() * thrCount) / log(EdgeSize) + 0.5;
    source = Node(board, color);
    root = &source;
}
//removes any child that isn't keep
void Bot::trim(Node *parent, Node *keep)
{
    for (auto child : parent->children)
        if (child != keep)
            delete child;
    parent->children[0] = keep;
    parent->children.resize(1);
}
void Bot::countdown(system_clock::time_point start, milliseconds thinkTime, Node *root, float depth, int threadCount)
{
    milliseconds timepast;
    do
    {
        timepast = duration_cast<milliseconds>(system_clock::now() - start);
        root->explore(round(depth - log(timepast.count() * threadCount) / log(EdgeSize)));
    } while (timepast < thinkTime);
}
//makes a play and returns the board
int8_t *Bot::play(int8_t board[BoardSize])
{
    system_clock::time_point start = system_clock::now();
    enemyMove(board);
    root->clean();
    vector<thread> jobs;
    for (int i = 0; i < threadCount; i++)
        jobs.emplace_back(countdown, start, timeLimit, root, depth, threadCount);
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
    {
        cout << "Winner: " << (root->gameover == 1 ? "Black\n" : "White\n");
        timeLimit = milliseconds(1);
    }
    move();
    return root->board;
}
//updates root to the most visited child node
void Bot::move()
{
    Node *best = root->children.front();
    for (auto child : root->children)
        if (child->totalGames > best->totalGames)
            best = child;
    for (auto child : root->children)
        if (child->gameover == root->col)
            best = child;
    threadVec.emplace_back(trim, root, best);
    root = best;
}
//changes root if there's a child with such board
void Bot::enemyMove(int8_t target[BoardSize])
{
    for (auto child : root->children)
        if (equal(child->board, child->board + BoardSize, target))
        {
            threadVec.emplace_back(trim, root, child);
            root = child;
        }
}