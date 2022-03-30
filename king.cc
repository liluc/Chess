#include "king.h"
#include "piece.h"
#include <vector>
using namespace std;

King::King(Board * board, Cell *cell, int player):Piece{board, cell, player, "king"}{}

vector<vector<char>> King::possibleMoves(){
    vector<vector<char>> cells;
    addCell(1, 0, cells);
    addCell(-1, 0, cells);
    addCell(0, 1, cells);
    addCell(0, -1, cells);
    addCell(1, 1, cells);
    addCell(1, -1, cells);
    addCell(-1, 1, cells);
    addCell(-1, -1, cells);
    return cells;
}

King::~King(){}
