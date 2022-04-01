#ifndef _PIECE_H_
#define _PIECE_H_
#include "board.h"
#include "cell.h"
#include <vector>
#include <string>

// Cell's implementation doesn't use any methods of other classes, so cell forward declares Piece
// class Cell;
class Board;
class InvalidMove {
    public:
    InvalidMove();
    ~InvalidMove();
};  // error type

class Piece{
    Cell *cell;
    Board *board;
    int player;
    std::string type;

public:
    Piece(Cell *, int);
    public:
    Piece(Board *, Cell *, int, std::string);
    
    std::vector<char> getPos();

    Cell *getCell();

    Board *getBoard();

    int getPlayer();

    bool checkBound(std::vector<char>);

    std::string getType();

    bool checkPlayer(Piece *);

    bool contained(std::vector<std::vector<char>>, std::vector<char>);

    bool addCell(char colInc, char rowInc, std::vector<std::vector<char>> &cells);

    //returns true if king of player of this piece is checked
    //require: king of current player must exists
    virtual bool isChecked();

    Piece * createPiece(Cell *);

    virtual std::vector<std::vector<char>> possibleMoves() = 0;
    void move(std::vector<char>);
    virtual ~Piece();
    /* suggestions
    string getType() const;
    */
};

#endif
