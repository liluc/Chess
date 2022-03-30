#include "piece.h"
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

bool Piece::addCell(char colInc, char rowInc, vector<vector<char>> &cells){
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
