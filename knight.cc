#include "knight.h"
#include "piece.h"
#include <vector>
#include <iostream>
using namespace std;

Knight::Knight(Board *board, Cell *cell, int player):Piece{board, cell, player, "night"}{}

vector<vector<char>> Knight::possibleMoves(){
    //testing cout
    // cout << "in possible moves of knight" << endl;

    vector<vector<char>> cells;
    addCell(1, 2, cells);
    addCell(2, 1, cells);
    addCell(-1, 2, cells);
    addCell(-2, 1, cells);
    addCell(1, -2, cells);
    addCell(2, -1, cells);
    addCell(-1, -2, cells);
    addCell(-2, -1, cells);

    //testing cout
    // cout << "end of possible moves of knight" << endl;
    return cells;
}

Knight::~Knight(){}
