#ifndef _HISTORY_H_
#define _HISTORY_H_
#include <vector>

class Board;
class History{
    std::vector<Board *> *histBoard;
    public:
    History();
    void push(Board *);
    Board *pop();
    Board *top();
    ~History();
}
