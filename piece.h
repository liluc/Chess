#ifndef _PIECE_H_
#define _PIECE_H_
#include "board.h"
#include "cell.h"
#include "exception.h"
#include <vector>
#include <string>

// Cell's implementation doesn't use any methods of other classes, so cell forward declares Piece
// class Cell;
class Board;
// error type moved in seperate header file

class Piece{
    Cell *cell;
    Board *board;
    int player;
    std::string type;
    public:
    Piece(Board *, Cell *, int, std::string);
    
    std::vector<char> getPos() const;

    Cell *getCell() const;

    Board *getBoard() const;

    int getPlayer() const;

    bool checkBound(std::vector<char>);

    std::string getType() const;

    bool checkPlayer(Piece *);

    bool contained(std::vector<std::vector<char>>, std::vector<char>) const;

    bool addCell(char colInc, char rowInc, std::vector<std::vector<char>> &cells);

    //returns true if king of player of this piece is checked
    //require: king of current player must exists
    virtual bool isChecked() const;

    Piece * createPiece(Cell *);

    virtual std::vector<std::vector<char>> possibleMoves() = 0;
    void move(std::vector<char>);
    virtual ~Piece();
    /* suggestions
    string getType() const;
    */
};

#endif
