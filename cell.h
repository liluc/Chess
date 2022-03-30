#ifndef __CELL_H__
#define __CELL_H__

#include <vector>

class Piece;

class Cell
{
    Piece *piece;
    std::vector<char> position;

public:
    Cell(std::vector<char>, Piece * = nullptr);
    ~Cell();
    Piece *getPiece() const;
    void setPiece(Piece *);
    std::vector<char> getPos() const;
};

#endif
