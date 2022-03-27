#ifndef _PAWN_H_
#define _PAWN_H_
#include <vector>
#include "piece.h"

class Cell;
class Pawn : public Piece{
    int steps;
    public:
    Pawn(Cell *, int, int);
    std::vector<std::vector<char>> possibleMoves() override;
    void move(std::vector<char>) override;
    void promote();
    ~Pawn();
};

#endif
