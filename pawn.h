#ifndef _PAWN_H_
#define _PAWN_H_
#include <vector>
#include "piece.h"

class Cell;
class Board;
class Pawn : public Piece{
    int steps;
    void addCell_PawnMove (char colInc, char rowInc, vector<vector<char>> &cells);
    void addCell_PawnCapture (char colInc, char rowInc, vector<vector<char>> &cells);
    public:
    Pawn(Board *, Cell *, int, int);
    std::vector<std::vector<char>> possibleMoves() override;
    void promote(string type);
    ~Pawn();
};

#endif
