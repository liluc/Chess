#ifndef _BISHOP_H_
#define _BISHOP_H_
#include <vector>
#include "piece.h"

class Cell;
class Board;
class Bishop : public Piece{
    bool addCell(char colInc, char rowInc, vector<vector<char>> &cells);
    public:
    Bishop(Board *, Cell *, int);
    std::vector<std::vector<char>> possibleMoves() override;
    ~Bishop();
};

#endif