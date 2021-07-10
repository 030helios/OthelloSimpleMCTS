#include "func.h"
#include "node.h"
using namespace std;

Node::~Node()
{
    for (auto child : children)
        delete child;
}
Node::Node(int8_t *bd, int8_t col) : color(col), shuffleID(rand() % randomness)
{
    copy(bd, bd + BoardSize, board);
    sem_init(&sem, 0, 1);
}
//removes data without removing the structure
void Node::clean()
{
    totalScore = 0;
    totalGames = 0;
    for (auto child : children)
        child->clean();
}
//initializes new child if possible
Node *Node::getNewChild()
{
    Node *child = new Node(board, -color);
    if (newMove(child->board, color, shuffleID, moveIndex))
        children.emplace_back(child);
    else if (children.size() > 0) // has children
    {
        delete child;
        return nullptr;
    }
    else if (!hasMove(board, -color)) //won
    {
        delete child;
        return nullptr;
    }
    else //pass
        children.emplace_back(child);
    return children.back();
}
float Node::UCB(int N, int8_t parentColor)
{
    if (gameover != -2)
        if (gameover != 0)
            return N * parentColor * gameover;
        else
            return 0.5 + sqrt(2 * log(N) / (float)totalGames);
    float a = sqrt(2 * log(N) / (float)totalGames);
    a += 0.5 + (float)(totalScore) / (parentColor * 2 * totalGames);
    return a;
}
//returns child with greatest UCB
Node *Node::select()
{
    float ucbmax = -INFINITY;
    Node *best = nullptr;
    for (auto child : children)
    {
        sem_wait(&child->sem);
        if (child->totalGames == 0)
        {
            sem_post(&child->sem);
            return child;
        }
        float ucb = child->UCB(totalGames, color);
        if (ucb > ucbmax)
        {
            ucbmax = ucb;
            best = child;
            gameover = child->gameover;
        }
        sem_post(&child->sem);
    }
    return best;
}
//Heat determines whether to allocate new child or not
int Node::explore(int8_t heat)
{
    Node *child = nullptr;
    sem_wait(&sem);
    totalGames++;
    if (gameover != -2 && gameover != 0)
    {
        sem_post(&sem);
        return gameover;
    }
    if (heat == 0)
    {
        totalScore = playout(board, color);
        sem_post(&sem);
        return totalScore;
    }
    if (moveIndex >= 0)
        child = getNewChild();
    if (child == nullptr)
        child = select();
    else
        heat--;
    if (child == nullptr) //won
    {
        gameover = score(board);
        sem_post(&sem);
        return gameover;
    }
    sem_post(&sem);
    int outcome = child->explore(heat);
    sem_wait(&sem);
    totalScore += outcome;
    if (gameover != -2 && gameover != 0)
    {
        outcome = totalGames * gameover - totalScore;
        totalScore = gameover * totalGames;
    }
    sem_post(&sem);
    return outcome;
}