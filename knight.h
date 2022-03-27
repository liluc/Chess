#ifndef _KNIGHT_H_
#define _KNIGHT_H_
#include <vector>
#include "piece.h"

class Cell;
class Knight : public Piece{
    public:
    Knight(Cell *, int);
    std::vector<std::vector<char>> possibleMoves() override;
    void move(std::vector<char>) override;
    ~Knight();
};

#endif
