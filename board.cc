#include "board.h"

Board::Board()
{
    vector<vector<Cell *>> b;
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
}

Cell *Board::getCell(vector<char> pos) const
{
    int col = pos.at(0) - 'a';
    int row = pos.at(1) - '1';
    return board.at(col).at(row);
}
void Board::setPiece(Piece *p, vector<char> pos)
{
    getCell(pos)->setPiece(p);
}

Piece *Board::checkPos(vector<char> pos) const
{
    return getCell(pos)->getPiece();
}

// NVI idiom
void Board::movePiece(vector<char> start, vector<char> end)
{
    Piece *curpiece = checkPos(start);

    if (!(curplace))
        return;
    try
    {
        move(curpiece, end); // this move is a virtual function
    }
    catch (InvalidMove *im)
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
