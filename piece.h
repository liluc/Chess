#ifndef _PIECE_H_
#define _PIECE_H_
#include "board.h"
#include <vector>
#include <string>
#include "invalidmove.h"

class Cell;
class Board;
class Piece{
    Cell *cell;
    Board *board;
    int player;
    /* suggestions
    string type;    note: type for Knight is "night" for convenience
    */

public:
    Piece(Cell *, int);
    std::string type;

    public:

    // true if the target position contains a piece(no matter that is from the same player or not)
    bool addCell(char, char, std::vector<std::vector<char>> &);

    Piece(Board *, Cell *, int, std::string);
    
    std::vector<char> getPos();

    Cell *getCell();

    Board *getBoardPtr();

    int getPlayer();

    bool checkBound(Cell *);

    std::string getType();

    bool checkPlayer(Piece *);

    bool contained(std::vector<std::vector<char>>, std::vector<char>);

    virtual std::vector<std::vector<char>> possibleMoves() = 0;
    void move(std::vector<char>);
    virtual ~Piece();
    /* suggestions
    string getType() const;
    */
};

#endif
