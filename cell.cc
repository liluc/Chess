#include "cell.h"

Cell::Cell(vector<char> pos, Piece *p = nullptr) : piece{p}, position{pos} {}

Cell::~Cell()
{
    delete piece;
}

Piece *Cell::getPiece() const
{
    return piece;
}

vector<char> Cell::getpos() const
{
    return position;
}

void Cell::setPiece(Piece *p)
{
    delete piece;
    piece = p;
}
