#ifndef __BOARD_H__
#define __BOARD_H__

#include "cell.h"
#include "piece.h"
#include <vector>
#include "observer.h"
#include "subject.h"

class Board : public Subject
{
    std::vector<Piece *> pieces;
    std::vector<std::vector<Cell *>> board;
    bool ended;
    int turn;
    const int BOARDSIZE = 8;

public:
    Board();
    ~Board();
    void EmptyBoard();
    bool getState() const;
    std::vector<std::vector<Cell *>> getBoard() const;
    std::vector<Piece *> getPieces() const;
    void removePiece(Piece *);
    void pushPieces(Piece *);
    int getTurn() const;
    Cell *getCell(std::vector<char>) const;

    void setState(bool);
    void setPiece(Piece *, std::vector<char>);
    void setTurn(int);
    Piece *checkPos(std::vector<char>) const;
    void movePiece(std::vector<char>, std::vector<char>);

    // isStalemate observes the board and returns true if for the current
    // player, there are no possible moves
    bool isStalemate() const;
    void isCheckmate() const;

    // void notify() override;
};

#endif
