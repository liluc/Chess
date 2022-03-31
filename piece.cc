#include "piece.h"
#include "king.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "queen.h"
#include "bishop.h"
#include <vector>
#include <string>
using namespace std;

Piece::Piece(Board *board, Cell *cell, int player, string type):board{board}, cell{cell}, player{player}, type{type}{}

vector<char> Piece::getPos(){
    return cell->getPos();
}

Cell * Piece::getCell(){
    return cell;
}

Board * Piece::getBoard(){
    return board;
}

int Piece::getPlayer(){
    return player;
}

string Piece::getType(){
    return type;
}

bool Piece::checkBound(Cell *cell){
    vector<char> pos = getPos();
    if (pos[0] >= 'a' && pos[0] <= 'h'){
        if (pos[1] >= '1' && pos[1] <= '8'){
            return true;
        }
    }
    return false;
}

//check if the player of this piece is the same as the other piece
bool Piece::checkPlayer(Piece *other){
    return player == other->getPlayer();
}

//pos must have two entries only!!!!
bool Piece::contained(vector<vector<char>> posList, vector<char> pos){
    for (auto x : posList){
        if (x[0] != pos[0] || x[1] != pos[1]) return false;
    }
    return true;
}

void Piece::move(vector<char> pos){
    if (Piece::contained(possibleMoves(), pos)){
        Cell *targetCell = Piece::getBoard()->getCell(pos);
        delete targetCell->getPiece();
        targetCell->setPiece(this);
        cell->setPiece(nullptr);
        
    } else {
        InvalidMove invalid;
        throw invalid ;
    }
}

bool Piece::isChecked(){
    vector<vector<Cell *>> cells = board->getBoard();
    for (auto col : cells){
        for (auto x : col){
            Piece *piece = x->getPiece();
            if (piece->getType() == "king"){
                if(piece->getPlayer() == player){
                    return piece->isChecked();
                } 
            }
        }
    }
}

Piece * Piece::createPiece(Cell *targetCell){
    if (type == "king"){
        return new King{targetCell,  player};
    } 
    else if (type == "queen"){
        return new Queen{targetCell,  player};
    }
    else if (type == "night"){
        return new Knight{targetCell,  player};
    }
    else if (type == "bishop"){
        return new Bishop{targetCell,  player};
    }
    else if (type == "rook"){
        return new Rook{targetCell,  player};
    }
    else if (type == "Pawn"){
        return new Pawn{targetCell,  player};
    }
}


//board.h
//void setPiece(Piece *, std::vector<char>);

//if now we are checked, then possible moves only includes that can make us unchecked after the move.(i.e. either 
//  capturing the piece, blocking the piece, or move the king)
//1. create a temp piece at target position.
//2. detach this piece with the cells, attach temp piece with the target position.
//3. check with the temp piece if isChecked is still true
//4. if isChecked is false, add the target position into list
//5. delete temp, attach this with current cell
bool Piece::addCell(char colInc, char rowInc, vector<vector<char>> &cells){
    if (isChecked()){
        Piece *temp = new 
    }
    vector<char> currentPos = getPos();
    char newCol = currentPos[0] + colInc;
    char newRow = currentPos[1] + rowInc;
    vector<char> targetPos {newCol, newRow};
    Cell *targetCell = getBoard()->getCell(targetPos);
    if (checkBound(targetCell)) cells.emplace_back(targetPos);
    if (targetCell->getPiece() != nullptr){
        if (checkPlayer(targetCell->getPiece())){
            cells.pop_back();
        }
        return true;
    }
    return false;
}
Piece::~Piece(){};
