#include "pawn.h"
#include "cell.h"
#include "piece.h"
#include "queen.h"
#include "knight.h"
#include "rook.h"
#include "bishop.h"
#include <vector>
using namespace std;

Pawn::Pawn(Board *board, Cell *cell, int player, int steps):Piece{board, cell, player, "pawn"}, steps{steps}{}

int abs(int n){
    return n > 0? n : -n;
}

void Pawn::addCell_PawnMove (char colInc, char rowInc, vector<vector<char>> &cells){
    vector<char> currentPos = getPos();
    char newCol = currentPos[0] + colInc;
    char newRow = currentPos[1] + rowInc;
    vector<char> targetPos {newCol, newRow};
    Cell *targetCell = getBoard()->getCell(targetPos);
    if (checkBound(targetCell)){
        if (targetCell->getPiece() == nullptr){
            cells.emplace_back(targetPos);
            steps += abs(colInc);
        }
    } 
}

void Pawn::addCell_PawnCapture (char colInc, char rowInc, vector<vector<char>> &cells){
    vector<char> currentPos = getPos();
    char newCol = currentPos[0] + colInc;
    char newRow = currentPos[1] + rowInc;
    vector<char> targetPos {newCol, newRow};
    Cell *targetCell = getBoard()->getCell(targetPos);
    if (checkBound(targetCell)){
        if (targetCell->getPiece() != nullptr){
            if (targetCell->getPiece()->getPlayer() != getPlayer()){
                cells.emplace_back(targetPos);
                steps += abs(colInc);
            }
        } 
    } 
}

    // std::vector<std::vector<char>> possibleMoves() override;
    // void move(std::vector<char>) override;
    // void promote();
    // ~Pawn();
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

void Pawn::promote(string type){
    //would it be better to put promote() in board? or keep it in pawn.
    // if (9 % getPos()[1] == 1){
    //     Cell *promoteCell = getCell();
    //     if(type == "Q") promoteCell->setPiece(new Queen(getBoardPtr(), promote, ));
        

    // }
    
}

Pawn::~Pawn(){}
