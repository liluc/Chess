#include "bishop.h"
#include "piece.h"
#include <vector>
#include <iostream>
using namespace std;

Bishop::Bishop(Board *board, Cell *cell, int player):Piece{board, cell, player, "bishop"}{}

vector<vector<char>> Bishop::possibleMoves(){
    vector<vector<char>> cells;
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

Bishop::~Bishop(){

}
