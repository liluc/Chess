#include "cell.h"
#include <iostream>
using namespace std;

Cell::Cell(vector<char> pos, Piece *p) : piece{p}, position{pos} {}

Cell::~Cell() {}  // pieces are already deleted in Board

Piece *Cell::getPiece() const
{
    return piece;
}

vector<char> Cell::getPos() const
{
    return position;
}

void Cell::setPiece(Piece *p)
{
    piece = p;
}
