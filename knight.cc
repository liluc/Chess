#include "knight.h"
#include "piece.h"
#include <vector>
using namespace std;

Knight::Knight(Board *board, Cell *cell, int player):Piece{board, cell, player, "night"}{}

vector<vector<char>> Knight::possibleMoves(){
    vector<vector<char>> cells;
    addCell(1, 2, cells);
    addCell(2, 1, cells);
    addCell(-1, 2, cells);
    addCell(-2, 1, cells);
    addCell(1, -2, cells);
    addCell(2, -1, cells);
    addCell(-1, -2, cells);
    addCell(-2, -1, cells);
}

Knight::~Knight(){}
