#include "board.h"
#include <iostream>
#include "exception.h"
using namespace std;

Board::Board()
{
    vector<vector<Cell *>> b;
    vector<Piece *> p;
    for (int i = 0; i < BOARDSIZE; ++i)
    // i  is the col column of the cell, 'a' to 'h'
    {
        vector<Cell *> col;
        for (int j = 0; j < BOARDSIZE; ++j)
        {
            // j is the row of the cell, '1' to '8'
            char c = 'a' + i;
            char r = '1' + j;
            vector<char> pos{c, r};
            Cell *newcell = new Cell{pos};
            col.emplace_back(newcell);
        }
        b.emplace_back(col);
    }
    board = b;
    pieces = p;
    turn = 1;
}

Board::~Board()
{
    for (auto col : board)
    {
        for (auto cell : col)
        {
            delete cell;
        }
    }
    for (auto piece : pieces)
    {
        delete piece;
    }
}

bool Board::getState() const
{
    return ended;
}

void Board::setState(bool term) {
    ended = term;
}

vector<Piece *> Board::getPieces() const
{
    return pieces;
}

vector<vector<Cell *>> Board::getBoard() const
{
    return board;
}

Cell *Board::getCell(vector<char> pos) const
{
    int col = pos.at(0) - 'a';
    int row = pos.at(1) - '1';
    return board.at(col).at(row);
}

int Board::getTurn() const
{
    return turn;
}

Piece *Board::checkPos(vector<char> pos) const
{
    return getCell(pos)->getPiece();
}

// setters 
void Board::setTurn(int t) {
    turn = t;
}

void Board::setPiece(Piece *p, vector<char> pos)
{
    Piece *old = checkPos(pos);
    int size = pieces.size();
    for (int i = 0; i < size; ++i)
    {
        if (pieces.at(i) == old) // compare by mem address
        {
            pieces.erase(pieces.begin() + i);
            return;
        }
    }
    delete old;
    getCell(pos)->setPiece(p);
    pieces.emplace_back(p);
}

// NVI idiom

void Board::movePiece(vector<char> start, vector<char> end)
{

    Piece *curpiece = checkPos(start);
    Piece *destpiece = checkPos(end);
    if (!(curpiece))
        return;
    try
    {
        curpiece->move(end);
        notifyObservers();
    }
    catch (InvalidMove &im)
    {
        throw;
    }
}

/*
bool Board::isStalemate() const
{
    if (->)
    bool stale{true};
    for (auto piece : pieces) {
        if (((turn % 2) + 1) != piece->getPlayer())
            continue;
        stale = stale && (piece->possibleMoves().size() == 0);
    }
    return stale;
}

bool Board::isCheckmate() const {
    bool mate{true};

} */
