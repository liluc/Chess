#include "bishop.h"
#include "piece.h"
#include <vector>
using namespace std;

Bishop::Bishop(Board *board, Cell *cell, int player):Piece{board, cell, player, "bishop"}{}

//true if the target position contains a piece(no matter that is from the same player or not)
bool Bishop::addCell(char colInc, char rowInc, vector<vector<char>> &cells){
    vector<char> currentPos = Piece::getPos();
    char newCol = currentPos[0] + colInc;
    char newRow = currentPos[1] + rowInc;
    vector<char> targetPos {newCol, newRow};
    Cell *targetCell = Piece::getBoard()->getCell(targetPos);
    if (Piece::checkBound()) cells.emplace_back(targetPos);
    if (targetCell->getPiece() != nullptr){
        if (checkPlayer(targetCell->getPiece())){
            cells.pop_back();
        }
        return true;
    }
    return false;
}

vector<vector<char>> Bishop::possibleMoves(){
    vector<vector<char>> cells;
    for (int col = 0, row = 0; col < 8, row < 8; ++col, ++row){ // move towards top right
        if (addCell(col, row, cells)) break;
    }
    for (int col = 0, row = 0; col > -8, row < 8; --col, ++row){ // move towards top left
        if (addCell(col, row, cells)) break;
    }
    for (int col = 0, row = 0; col < 8, row > -8; ++col, --row){ // move towards down right
        if (addCell(col, row, cells)) break;
    }
    for (int col = 0, row = 0; col > -8, row > -8; --col, --row){ // move towards down left
        if (addCell(col, row, cells)) break;
    }
    return cells;
}

Bishop::~Bishop(){}
