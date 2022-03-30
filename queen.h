#ifndef _QUEEN_H_
#define _QUEEN_H_
#include <vector>
#include "piece.h"

class Cell;
class Queen : public Piece{
    public:
    Queen(Cell *, int);
    std::vector<std::vector<char>> possibleMoves() override;
    void move(std::vector<char>) override;
    ~Queen();
};

#endif
