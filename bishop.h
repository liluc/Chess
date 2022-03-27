#ifndef _BISHOP_H_
#define _BISHOP_H_
#include <vector>
#include "piece.h"

class Cell;
class Bishop : public Piece{
    public:
    Bishop(Cell *, int);
    std::vector<std::vector<char>> possibleMoves() override;
    void move(std::vector<char>) override;
    ~Bishop();
};

#endif
