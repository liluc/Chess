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
    turn = 0;
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

void Board::EmptyBoard() {
    for (auto piece : pieces) {
        delete piece;
    }

    vector<Piece *> new_pieces;
    pieces = new_pieces;

    for (auto col : board) {
        for (auto cell : col) {
            cell->setPiece(nullptr);
        }
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

void Board::removePiece(Piece *piece){
    int size = pieces.size();
    for (int i = 0; i < size; ++i)
    {
        if (pieces.at(i) == piece) // compare by mem address
        {
            pieces.erase(pieces.begin() + i);
            return;
        }
    }
}

void Board::setPiece(Piece *p, vector<char> pos)
{
    Piece *old = checkPos(pos);
    removePiece(old);
    delete old;
    getCell(pos)->setPiece(p);
    pieces.emplace_back(p);
    notifyObservers();
}


void Board::pushPieces(Piece *piece){
    pieces.emplace_back(piece);
}

// NVI idiom

void Board::movePiece(vector<char> start, vector<char> end)
{
    //testing cout
    // cout << "board: movepiece" << endl;
    Piece *curpiece = checkPos(start);
    Piece *destpiece = checkPos(end);
    if (!(curpiece))
        return;
    if (curpiece->getPlayer() != (turn % 2) + 1) {
        cerr << "This piece doesn't belong to you, you moron!" << endl;
        InvalidMove im;
        throw im;
    }
    try
    {
        curpiece->move(end);
        notifyObservers();
    }
    catch (InvalidMove &im)
    {
        throw;
    }
    turn += 1;

    //testing cout
    // cout << "board movePiece end" << endl;
}

/*
bool Board::CheckAfterMove(vector<char> start, vector<char> end) {
    Piece *curpiece = checkPos(start);
    Piece *destpiece = checkPos(end);
    getCell(end)->setPiece(nullptr, end);

    curpiece->move(end);
    bool checked = turn % 2
}
*/
