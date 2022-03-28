#include "rook.h"
#include "piece.h"
#include <vector>
#include <stdexcept>
#include "cell.h"
#include "board.h"
using namespace std;

class InvalidMove{};

Rook::Rook(Cell *cell, int player):Piece{cell, player}{}

vector<vector<char>> Rook::possibleMoves(){
    vector<char> currentPos = Piece::getPos();
    vector<vector<char>> cells;
    for (int col = 0; col < 8; ++col){
        char newCol = currentPos[0] + col;
        vector<char> targetPos {newCol, currentPos[1]};
        Cell *targetCell = Piece::getBoard()->getCell(targetPos);
        if (newCol >= 'a' && newCol <= 'h') cells.emplace_back(targetPos);
        if (targetCell->getPiece() != nullptr){
            if (targetCell->getPiece()->getPlayer() == ) // need to determine if the player of this piece equals to the player of turn
        } break;
    }
    for (int col = 0; col > -8; --col){
        char newCol = currentPos[0] + col;
        vector<char> targetPos {newCol, currentPos[1]};
        Cell *targetCell = Piece::getBoard()->getCell(targetPos);
        if (newCol >= 'a' && newCol <= 'h') cells.emplace_back(targetPos);
        if (targetCell->getPiece() != nullptr) break;
    }
    for (int row = 0; row < 8; ++row){
        char newRow = currentPos[0] + row;
        vector<char> targetPos {currentPos[0], newRow};
        Cell *targetCell = Piece::getBoard()->getCell(targetPos);
        if (newRow >= '1' && newRow <= '8') cells.emplace_back(targetPos);
        if (targetCell->getPiece() != nullptr) break;
    }
    for (int row = 0; row > -8; --row){
        char newRow = currentPos[0] + row;
        vector<char> targetPos {currentPos[0], newRow};
        Cell *targetCell = Piece::getBoard()->getCell(targetPos);
        if (newRow >= '1' && newRow <= '8') cells.emplace_back(targetPos);
        if (targetCell->getPiece() != nullptr) break;
    }
    return cells;
}

//consider if there's some piece on the way of move
void Rook::move(vector<char> pos){
    if (Piece::contained(possibleMoves, pos)){
        Cell *targetCell = Piece::getBoard()->getCell(pos);
        delete targetCell->getPiece();
        targetCell->setPiece(this);
        cell->setPiece(nullptr);
        cell->targetCell;
        
    } else {
        throw InvalidMove;
    }
}

Rook::~Rook(){}
