#include "queen.h"
#include "piece.h"
#include <vector>
using namespace std;

Queen::Queen(Board *board, Cell *cell, int player):Piece{board, cell, player, "queen"}{}

vector<vector<char>> Queen::possibleMoves(){
    vector<vector<char>> cells;
    for (int colInc = 1; colInc < 8; ++colInc){ //horizontal move right
        if (addCell(colInc, 0, cells)) break;
    }
    for (int colInc = -1; colInc > -8; --colInc){ //horizontal move left
        if (addCell(colInc, 0, cells)) break;
    }
    for (int rowInc = 1; rowInc < 8; ++rowInc){ //vertical move up
        if (addCell(0, rowInc, cells)) break;
    }
    for (int rowInc = -1; rowInc > -8; ++rowInc){ //vertical move down
        if (addCell(0, rowInc, cells)) break;
    }
    for (int col = 1, row = 1; col < 8, row < 8; ++col, ++row){ // move towards top right
        if (addCell(col, row, cells)) break;
    }
    for (int col = -1, row = 1; col > -8, row < 8; --col, ++row){ // move towards top left
        if (addCell(col, row, cells)) break;
    }
    for (int col = 1, row = -1; col < 8, row > -8; ++col, --row){ // move towards down right
        if (addCell(col, row, cells)) break;
    }
    for (int col = -1, row = -1; col > -8, row > -8; --col, --row){ // move towards down left
        if (addCell(col, row, cells)) break;
    }
    return cells;
}


Queen::~Queen(){}
