#include "board.h"

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
            vector<char> pos{'a' + i, '1' + j};
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

bool Board::getstate() const
{
    return ended;
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

Piece *Board::checkPos(vector<char> pos) const
{
    return getCell(pos)->getPiece();
}

void Board::setPiece(Piece *p, vector<char> pos)
{
    Piece *old = checkPos(pos);
    for (int i = 0; i < pieces.size(); ++i)
    {
        if (pieces.at(i) == old) // compare by mem address
        {
            pieces.erase(i);
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
    if (destpiece)
    {
        for (int i = 0; i < pieces.size(); ++i)
        {
            if (pieces.at(i) == destpiece)
            {
                pieces.erase(i);
                return;
            }
        }
        delete destpiece;
    }
    if (ended)
        cerr << "Game is already ended, please start a new game" << endl;

    if (!(curplace))
        return;
    try
    {
        move(curpiece, end);
        // this move is a virtual function
        if (isStalemate())
            ended = true;
    }
    catch (InvalidMove &im)
    {
        throw;
    }
}

bool Board::isStalemate() const
{
    bool stale{true};
    for (auto col : board)
    {
        for (auto cell : col)
        {
            if (!(checkPos()))
                continue;
            if ((turn % 2) != cell->piece->getplayer())
                continue;
            stale = stale && (cell->piece->possible_moves().size() == 0);
        }
    }

    return stale;
}
