#ifndef _ROOK_H_
#define _ROOK_H_
#include <vector>
#include "piece.h"

class Cell;
class Board;
class Rook : public Piece{
    public:
    Rook(Board *, Cell *, int);
    std::vector<std::vector<char>> possibleMoves() override;
    void move(std::vector<char>) override;
    ~Rook();
};

#endif
