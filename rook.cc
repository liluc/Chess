#include "rook.h"
#include "piece.h"
#include <vector>
#include <stdexcept>
#include "cell.h"
#include "board.h"
using namespace std;

class InvalidMove{};

Rook::Rook(Board *board, Cell *cell, int player):Piece{board, cell, player, "rook"}{}

vector<vector<char>> Rook::possibleMoves(){
    vector<vector<char>> cells;
    for (int colInc = 0; colInc < 8; ++colInc){ //horizontal move right
        if (addCell(colInc, 0, cells)) break;
    }
    for (int colInc = 0; colInc > -8; --colInc){ //horizontal move left
        if (addCell(colInc, 0, cells)) break;
    }
    for (int rowInc = 0; rowInc < 8; ++rowInc){ //vertical move up
        if (addCell(0, rowInc, cells)) break;
    }
    for (int rowInc = 0; rowInc > -8; ++rowInc){ //vertical move down
        if (addCell(0, rowInc, cells)) break;
    }
    return cells;
}

//consider if there's some piece on the way of move
// void Rook::move(vector<char> pos){
//     if (Piece::contained(possibleMoves(), pos)){
//         Cell *targetCell = Piece::getBoard()->getCell(pos);
//         delete targetCell->getPiece();
//         targetCell->setPiece(this);
//         cell->setPiece(nullptr);
//         cell->targetCell;
        
//     } else {
//         throw InvalidMove;
//     }
// }

Rook::~Rook(){}
