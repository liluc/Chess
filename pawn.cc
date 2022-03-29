#include "pawn.h"
#include "cell.h"
#include "piece.h"
#include <vector>
using namespace std;

Pawn::Pawn(Board *board, Cell *cell, int player, int steps):Piece{board, cell, player, "pawn"}, steps{steps}{}

void Pawn::addCell_PawnMove (char colInc, char rowInc, vector<vector<char>> &cells){
    vector<char> currentPos = getPos();
    char newCol = currentPos[0] + colInc;
    char newRow = currentPos[1] + rowInc;
    vector<char> targetPos {newCol, newRow};
    Cell *targetCell = getBoardPtr()->getCell(targetPos);
    if (checkBound(targetCell)){
        if (targetCell->getPiece() == nullptr){
            cells.emplace_back(targetPos);
        }
    } 
}

void Pawn::addCell_PawnCapture (char colInc, char rowInc, vector<vector<char>> &cells){
    vector<char> currentPos = getPos();
    char newCol = currentPos[0] + colInc;
    char newRow = currentPos[1] + rowInc;
    vector<char> targetPos {newCol, newRow};
    Cell *targetCell = getBoardPtr()->getCell(targetPos);
    if (checkBound(targetCell)){
        if (targetCell->getPiece() != nullptr){
            if (targetCell->getPiece()->getPlayer() != getPlayer()){
                cells.emplace_back(targetPos);
            }
        } 
    } 
}

vector<vector<char>> Pawn::possibleMoves(){
    vector<vector<char>> cells;
    vector<char> currentPos = getPos();
    if (getPlayer() == 1){
        addCell_PawnMove(1, 0, cells);
        addCell_PawnCapture(1, 1, cells);
        addCell_PawnCapture(1, -1, cells);
        if (getCell()->getPos()[1] == 1){
            addCell_PawnMove(2, 0, cells);
        }
    } else if (getPlayer() == 2){
        addCell_PawnMove(-1, 0, cells);
        addCell_PawnCapture(-1, 1, cells);
        addCell_PawnCapture(-1, -1, cells);
        if (getCell()->getPos()[1] == 1){
            addCell_PawnMove(-2, 0, cells);
        }
    }
    return cells;    
}

void Pawn::promote(){

}

Pawn::~Pawn(){}
