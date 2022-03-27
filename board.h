#ifndef __BOARD_H__
#define __BOARD_H__

#include "cell.h"
#include <vector>

class Board
{
    vector<vector<Cell *>> board;
    int turn;
    const int BOARDSIZE = 8;

public:
    Board();
    ~Board();
    Cell *getCell(vector<char>) const;
    void setPiece(Piece *, vector<char>);
    Piece *checkpos(vector<char>) const;
    void movePiece(vector<char>, vector<char>);

    // isStalemate observes the board and returns true if for the current
    // player, there are no possible moves
    bool isStalemate() const;
};

#endif
