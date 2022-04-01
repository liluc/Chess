#ifndef _PAWN_H_
#define _PAWN_H_
#include <vector>
#include "piece.h"

class Cell;
class Pawn : public Piece{
    int steps;
    public:
    Pawn(Board *, Cell *, int);
    void addCell_PawnMove (char colInc, char rowInc, std::vector<std::vector<char>> &cells);
    void addCell_PawnCapture (char colInc, char rowInc, std::vector<std::vector<char>> &cells);
    std::vector<std::vector<char>> possibleMoves() override;
    void promote(Piece *);
    ~Pawn();
};

#endif
