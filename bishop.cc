#include "bishop.h"
#include "piece.h"
#include <vector>
using namespace std;

Bishop::Bishop(Board *board, Cell *cell, int player):Piece{board, cell, player}{}


vector<vector<char>> Bishop::possibleMoves(){
    vector<char> currentPos = Piece::getPos();
    vector<vector<char>> cells;
    for (int col = 0, row = 0; col < 8, row < 8; ++col, ++row){ // move towards top right
        char newCol = currentPos[0] + col;
        char newRow = currentPos[1] + row;
        vector<char> targetPos {newCol, newRow};
        Cell *targetCell = Piece::getBoard()->getCell(targetPos);
        if (Piece::checkBound()) cells.emplace_back(targetPos);
        if (targetCell->getPiece() != nullptr) break;
    }
    for (int col = 0, row = 0; col > -8, row < 8; --col, ++row){ // move towards top left
        char newCol = currentPos[0] + col;
        char newRow = currentPos[1] + row;
        vector<char> targetPos {newCol, newRow};
        Cell *targetCell = Piece::getBoard()->getCell(targetPos);
        if (Piece::checkBound()) cells.emplace_back(targetPos);
        if (targetCell->getPiece() != nullptr) break;
    }
    for (int col = 0, row = 0; col < 8, row > -8; ++col, --row){ // move towards down right
        char newCol = currentPos[0] + col;
        char newRow = currentPos[1] + row;
        vector<char> targetPos {newCol, newRow};
        Cell *targetCell = Piece::getBoard()->getCell(targetPos);
        if (Piece::checkBound()) cells.emplace_back(targetPos);
        if (targetCell->getPiece() != nullptr) break;
    }
    for (int col = 0, row = 0; col > -8, row > -8; --col, --row){ // move towards down left
        char newCol = currentPos[0] + col;
        char newRow = currentPos[1] + row;
        vector<char> targetPos {newCol, newRow};
        Cell *targetCell = Piece::getBoard()->getCell(targetPos);
        if (Piece::checkBound()) cells.emplace_back(targetPos);
        if (targetCell->getPiece() != nullptr) break;
    }
    return cells;
}

void Bishop::move(vector<char>){
    
}

Bishop::~Bishop(){}
