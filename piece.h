#ifndef _PIECE_H_
#define _PIECE_H_
#include "board.h"
#include <vector>
#include <string>

class Cell;
class Board;
class Piece{
    Cell *cell;
    Board *board;
    int player;
    std::string type;
    public:
    Piece(Board *, Cell *, int, std::string);
    
    std::vector<char> getPos();

    Cell *getCell();

    Board *getBoard();

    int getPlayer();

    bool checkBound();

    std::string getType();

    bool checkPlayer(Piece *);

    bool contained(std::vector<std::vector<char>>, std::vector<char>);

    virtual std::vector<std::vector<char>> possibleMoves() = 0;
    void move(std::vector<char>);
    virtual ~Piece();
};

#endif
