#include "piece.h"
#include "king.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "queen.h"
#include "bishop.h"
#include <vector>
#include <iostream>
#include <string>
using namespace std;

Piece::Piece(Board *board, Cell *cell, int player, string type):board{board}, cell{cell}, player{player}, type{type}, enPableTurn{0}{}

vector<char> Piece::getPos() const{
    return cell->getPos();
}

Cell * Piece::getCell() const{
    return cell;
}

Board * Piece::getBoard() const{
    return board;
}

void Piece::setCell(Cell *c){
    cell = c;
}

int Piece::getPlayer() const{
    return player;
}

string Piece::getType() const{
    return type;
}

bool Piece::checkBound(vector<char> pos) const{
    if (pos[0] >= 'a' && pos[0] <= 'h'){
        if (pos[1] >= '1' && pos[1] <= '8'){
            return true;
        }
    }
    return false;
}

//check if the player of this piece is the same as the other piece
// bool Piece::checkPlayer(Piece *other){
//     return player == other->getPlayer();
// }

//pos must have two entries only!!!!
bool Piece::contained(vector<vector<char>> posList, vector<char> pos) const{
    for (auto x : posList){
        if (x[0] == pos[0] && x[1] == pos[1]) return true;
    }
    return false;
}

//set a piece to be enpable, which indicates that in next turn it could be captured by en passant
//when a piece takes the move of colInc = 0, rowInc = 2, enPable will be ture
//in this turn

void Piece::move(vector<char> pos){
    
    vector<vector<char>> possible = possibleMoves();

    //testing cout
    // cout << "# of possible moves: " << possible.size() << endl;
    // cout << "target pos " << pos[0] << pos[1] << endl;
    
    if (contained(possible, pos)){
        Cell *targetCell = Piece::getBoard()->getCell(pos);
        Piece *targetCellPiece = targetCell->getPiece();
        if (targetCellPiece){
            board->removePiece(targetCellPiece);
        }
        delete targetCellPiece;
        targetCell->setPiece(this);
        cell->setPiece(nullptr);
        cell = targetCell;
        if (board->getTurn() != enPableTurn){
            resetEnPable();
        }
        
    } else {
        InvalidMove invalid;
        throw invalid ;
    }
}

bool Piece::isChecked() const{
    vector<vector<Cell *>> cells = board->getBoard();
    for (auto col : cells){
        for (auto x : col){
            Piece *piece = x->getPiece();
            if (piece){
                if (piece->getType() == "king"){
                    if(piece->getPlayer() == player){
                        return piece->isChecked();
                    } 
                }
            }
        }
    }
}

void Piece::setEnPable(bool val){
    if (val){
        enPableTurn = board->getTurn();
    }

    //testing cout
    // cout << "enpable cell: " << getEnPableCell()->getPos()[0] << getEnPableCell()->getPos()[1] << endl;
}

// bool Piece::getEnPable(){ return false; }

void Piece::resetEnPable(){
    vector<Piece *> pieces = getBoard()->getPieces();
    for (auto piece : pieces){
        if (piece){
            if (piece->getType() == "pawn"){
                piece->setEnPable(false);
            }
        }
    }
}

int Piece::getEnPableTurn(){
    return enPableTurn;
}

Cell * Piece::getEnPableCell() const{return nullptr;}

Piece * Piece::createPiece(Cell *targetCell){
    if (type == "king"){
        return new King{board, targetCell,  player};
    } 
    else if (type == "queen"){
        return new Queen{board, targetCell,  player};
    }
    else if (type == "night"){
        return new Knight{board, targetCell,  player};
    }
    else if (type == "bishop"){
        return new Bishop{board, targetCell,  player};
    }
    else if (type == "rook"){
        return new Rook{board, targetCell,  player};
    }
    else if (type == "Pawn"){
        return new Pawn{board, targetCell,  player};
    }
}


//board.h
//void setPiece(Piece *, std::vector<char>);
//1. remove piece at pos
//2. connect cell at pos with piece at pos
//3. update vector<piece *>

//if now we are checked, then possible moves only includes that can make us unchecked after the move.(i.e. either 
//  capturing the piece, blocking the piece, or move the king)
//1. create a temp piece at target position.
//2. detach this piece with the cells, attach temp piece with the target position.
//3. check with the temp piece if isChecked is still true
//4. if isChecked is false, add the target position into list
//5. delete temp, attach this with current cell
//this points to original Piece
//temp points to temp Piece
//delete temp is requried
//return true if target position contains a piece. --> return true if target positi


//queen cannot capture, when king is checked, other pieces could still move!
bool Piece::addCell(int colInc, int rowInc, vector<vector<char>> &cells){
    vector<char> currentPos = getPos();
    char newCol = currentPos[0] + colInc;
    char newRow = currentPos[1] + rowInc;

    //testing cout
    // cout << "current type: " << getType() << endl;
    // cout << "current pos: " << currentPos[0] << currentPos[1] << endl;
    // cout << "new pos: " << newCol << newRow << endl;
    // if (!board->checkPos(vector<char> {'d', '8'})){
    //     cout << "d8 becomes empty!" << endl;
    //     cout << "happens before try to move " << currentPos[0] << currentPos[1] << " to " << newCol << newRow;
    // }
    //c8 has never become empty, when move d8 to c8, d8 becomes empty, how could this be
    //d8 becomes empty after one side is checked, is checked functions may be wrong

    
    vector<char> targetPos {newCol, newRow};
    if (checkBound(targetPos)){
        Cell *targetCell = getBoard()->getCell(targetPos);

        if (targetCell->getPiece() == nullptr){
            //testing cout
            // cout << "targetCell->getpiece is null " << endl;
            // cout << "target cell get: " << newCol << newRow << endl;
            //isChecked calls possible moves, possible moves calls addcell and addcell calls ischecked.
            // if (isChecked()){
                
                //testing cout 
                // cout << "current king is checked" << endl;

                // Piece *targetCellPiece = targetCell->getPiece(); // take the piece in the target cell off
                //if the piece is a piece of the current player, then the pos is invalid for sure
                Cell *originalCell = cell;

                // Piece *temp = createPiece(targetCell);
                cell->setPiece(nullptr);
                targetCell->setPiece(this);
                cell = targetCell;
                //if setPiece is used, then the current piece will get deleted, and targetCellPiece will get deleted.
                //so we cannot use it for now.
                if (!isChecked()){
                    //testing cout
                    cout << "by moving: " << originalCell->getPos()[0] << originalCell->getPos()[1] << " to " << targetPos[0] << targetPos[1] << endl;
                    cout << "king of " << getPlayer() << " is not checked" << endl;
                    cells.emplace_back(targetPos);
                }
                cell = originalCell;
                cell->setPiece(this);
                targetCell->setPiece(nullptr);
            // } else {
            //     //testing cout
            //     // cout << "current board is not checked" << endl;
            //     cells.emplace_back(targetPos);
            // }
        }

        else {
            if (targetCell->getPiece()->getPlayer() != player){

                // if (isChecked()){
                    Piece *targetCellPiece = targetCell->getPiece(); // take the piece in the target cell off
                    //if the piece is a piece of the current player, then the pos is invalid for sure
                    // Piece *temp = createPiece(targetCell);
                    Cell *originalCell = cell;
                    cell->setPiece(nullptr);
                    targetCell->setPiece(this);
                    targetCellPiece->setCell(nullptr);
                    cell = targetCell;
                    //if setPiece is used, then the current piece will get deleted, and targetCellPiece will get deleted.
                    //so we cannot use it for now.
                    if (!isChecked()){
                        cells.emplace_back(targetPos);
                    }
                    cell = originalCell;
                    cell->setPiece(this);
                    targetCell->setPiece(targetCellPiece);
                    targetCellPiece->setCell(targetCell);
                    
                    // delete temp;
                // } else {
                //     cells.emplace_back(targetPos);
                // }

            }
            
            return true;
        }
    }
    
    return false;
}
Piece::~Piece(){};
