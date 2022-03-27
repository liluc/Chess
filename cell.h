#ifndef __CELL_H__
#define __CELL_H__

#include <vector>

class Piece;

class Cell
{
    Piece *piece;
    vector<char> position;

public:
    Cell(vector<char>, Piece *);
    ~Cell();
    Piece *getPiece() const;
    void setPiece(Piece *);
    vector<char> getpos() const;
};

#endif
