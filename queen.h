#ifndef _QUEEN_H_
#define _QUEEN_H_
#include <vector>
#include "piece.h"

class Cell;
class Queen : public Piece{
    public:
    Queen(Board *, Cell *, int);
    std::vector<std::vector<char>> possibleMoves() override;
    ~Queen();
};

#endif
