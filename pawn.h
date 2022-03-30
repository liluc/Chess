#ifndef _PAWN_H_
#define _PAWN_H_
#include <vector>
#include "piece.h"

class Cell;
class Pawn : public Piece{
    int steps;
    public:
    Pawn(Board *, Cell *, int, int);
    void Pawn::addCell_PawnMove (char colInc, char rowInc, vector<vector<char>> &cells);
    void Pawn::addCell_PawnCapture (char colInc, char rowInc, vector<vector<char>> &cells);
    std::vector<std::vector<char>> possibleMoves() override;
    void promote(string type);
    ~Pawn();
};

#endif
