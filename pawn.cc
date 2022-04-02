#include "pawn.h"
#include "cell.h"
#include "piece.h"
#include "queen.h"
#include "knight.h"
#include "rook.h"
#include "bishop.h"
#include <vector>
#include <iostream>
using namespace std;

Pawn::Pawn(Board *board, Cell *cell, int player):Piece{board, cell, player, "pawn"}{
    if (player == 1){
        steps = cell->getPos()[1] - '0';
    } else {
        steps = '9' - cell->getPos()[1];
    }
}

int abs(int n){
    return n > 0? n : -n;
}

void Pawn::addCell_PawnMove (int colInc, int rowInc, vector<vector<char>> &cells){
    vector<char> currentPos = getPos();
    char newCol = currentPos[0] + colInc;
    char newRow = currentPos[1] + rowInc;

    //testing cout
    // cout << getPlayer() << endl;
    // cout << currentPos[0] << currentPos[1] << endl;
    // cout << newCol << newRow << endl;
    
    vector<char> targetPos {newCol, newRow};
    if (checkBound(targetPos)){
        Cell *targetCell = getBoard()->getCell(targetPos);
        if (targetCell->getPiece() == nullptr){
            cells.emplace_back(targetPos);
            steps += abs(colInc);
        }
    } 
    //testing cout
    // cout << cells.back()[0] << cells.back()[1] << endl;
}

void Pawn::addCell_PawnCapture (int colInc, int rowInc, vector<vector<char>> &cells){
    vector<char> currentPos = getPos();
    char newCol = currentPos[0] + colInc;
    char newRow = currentPos[1] + rowInc;
    vector<char> targetPos {newCol, newRow};
    if (checkBound(targetPos)){
        Cell *targetCell = getBoard()->getCell(targetPos);
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
    //testing cout
    // cout << "pawn possible move is called" << endl;
    vector<vector<char>> cells;
    vector<char> currentPos = getPos();
    if (getPlayer() == 1){
        addCell_PawnMove(0, 1, cells);
        addCell_PawnCapture(1, 1, cells);
        addCell_PawnCapture(-1, 1, cells);
        if (getCell()->getPos()[1] == '2'){
            addCell_PawnMove(0, 2, cells);
        }
    } else if (getPlayer() == 2){
        addCell_PawnMove(0, -1, cells);
        addCell_PawnCapture(1, -1, cells);
        addCell_PawnCapture(-1, -1, cells);
        if (getCell()->getPos()[1] == '7'){
            addCell_PawnMove(0, -2, cells);
        }
    }

    // testing cout
    // cout << currentPos[0] << currentPos[1] << endl;
    // cout << "in Cells:" << endl;
    // for (auto cell : cells){
    //     cout << cell[0] << cell[1] << endl;
    // }


    return cells;    
}

void Pawn::promote(Piece *targetPiece){
    getCell()->setPiece(targetPiece);
    delete this;
}

Pawn::~Pawn(){}
