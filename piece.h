#ifndef _PIECE_H_
#define _PIECE_H_
#include "board.h"
#include <vector>

class Cell;
class Board;
class Piece{
    Cell *cell;
    Board *board;
    int player;
    public:
    Piece(Board *, Cell *, int);
    std::vector<char> getPos();
    Cell *getcell();
    Board *getBoard()
    int getPlayer();
    bool contained(std::vector<std::vector<char>>, std::vector<char>);
    virtual std::vector<std::vector<char>> possibleMoves() = 0;
    virtual void move(std::vector<char>) = 0;
    virtual ~Piece();
};

#endif
