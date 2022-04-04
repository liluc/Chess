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

Pawn::Pawn(Board *board, Cell *cell, int player):Piece{board, cell, player, "pawn"}, enPable{false}, enPableCell{nullptr}{
    if (player == 1){
        steps = cell->getPos()[1] - '0';
    } else {
        steps = '9' - cell->getPos()[1];
    }
}

int abs(int n){
    return n > 0? n : -n;
}

void Pawn::setEnPable(bool val){
    enPable = val;
    if (!val) enPableCell = nullptr;
    Piece::setEnPable(val);
}

bool Pawn::getEnPable(){
    return enPable;
}

Cell * Pawn::getEnPableCell() const{
    return enPableCell;
}

bool Pawn::addCell_PawnMove (int colInc, int rowInc, vector<vector<char>> &cells){
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
        if (isChecked()){
                
            //testing cout 
            cout << "current king is checked" << endl;

            Piece *targetCellPiece = targetCell->getPiece(); // take the piece in the target cell off
            //if the piece is a piece of the current player, then the pos is invalid for sure
            Piece *temp = createPiece(targetCell);
            getCell()->setPiece(nullptr);
            targetCell->setPiece(temp);
            //if setPiece is used, then the current piece will get deleted, and targetCellPiece will get deleted.
            //so we cannot use it for now.
            if (!isChecked()){
                cells.emplace_back(targetPos);
            }
            getCell()->setPiece(this);
            targetCell->setPiece(targetCellPiece);
            delete temp;
        } else {
            if (targetCell->getPiece() == nullptr){
                cells.emplace_back(targetPos);
                steps += abs(colInc);
                return true;
            }
        }
    } 
    return false;
    //testing cout
    // cout << cells.back()[0] << cells.back()[1] << endl;
}

Piece * Pawn::isEnPableCell(Cell *c) const{
    vector<Piece *> pieces = getBoard()->getPieces();
    for (auto piece : pieces){
        if (piece->getType() == "pawn"){
            if (piece->getEnPableCell() == c){
                return piece;
            }
        }
    }
    return nullptr;
}

void Pawn::addCell_PawnCapture (int colInc, int rowInc, vector<vector<char>> &cells){
    vector<char> currentPos = getPos();
    char newCol = currentPos[0] + colInc;
    char newRow = currentPos[1] + rowInc;
    vector<char> targetPos {newCol, newRow};
    if (checkBound(targetPos)){
        Cell *targetCell = getBoard()->getCell(targetPos);
        if (isChecked()){
                
            //testing cout 
            cout << "current king is checked" << endl;

            Piece *targetCellPiece = targetCell->getPiece(); // take the piece in the target cell off
            //if the piece is a piece of the current player, then the pos is invalid for sure
            Piece *temp = createPiece(targetCell);
            getCell()->setPiece(nullptr);
            targetCell->setPiece(temp);
            //if setPiece is used, then the current piece will get deleted, and targetCellPiece will get deleted.
            //so we cannot use it for now.
            if (!isChecked()){
                cells.emplace_back(targetPos);
            }
            getCell()->setPiece(this);
            targetCell->setPiece(targetCellPiece);
            delete temp;
        }
        else {
            if (targetCell->getPiece() != nullptr){
                if (targetCell->getPiece()->getPlayer() != getPlayer()){
                cells.emplace_back(targetPos);
                steps += abs(colInc);
                }
            }
            else {
                //check en passant
                Piece * potentialEnpable = isEnPableCell(targetCell);
                if (potentialEnpable){
                    cells.emplace_back(targetPos);
                }
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
            if (addCell_PawnMove(0, 2, cells));
        }
    } else if (getPlayer() == 2){
        addCell_PawnMove(0, -1, cells);
        addCell_PawnCapture(1, -1, cells);
        addCell_PawnCapture(-1, -1, cells);
        if (getCell()->getPos()[1] == '7'){
            if (addCell_PawnMove(0, -2, cells));
        }
    }

    //checking en passant
    //en passant should be a method in pawn capture

    // testing cout
    // cout << currentPos[0] << currentPos[1] << endl;
    // cout << "in Cells:" << endl;
    // for (auto cell : cells){
    //     cout << cell[0] << cell[1] << endl;
    // }


    return cells;    
}

void Pawn::move(vector<char> pos){

    vector<vector<char>> possible = possibleMoves();

    //testing cout
    // cout << "# of possible moves: " << possible.size() << endl;
    // cout << "target pos " << pos[0] << pos[1] << endl;
    
    if (contained(possible, pos)){
        Cell *targetCell = Piece::getBoard()->getCell(pos);
        vector<char> currentPos = getCell()->getPos();
        
        //set enPableCell
        
        if (pos[0] - currentPos[0] == 0 &&
            abs(pos[1] - currentPos[1]) == 2){
            vector<char> enPablePos;
            Piece::setEnPable(true);
            if (getPlayer() == 1){
                enPablePos = vector<char> {currentPos[0], static_cast<char>(currentPos[1] - 1)};
            } else {
                enPablePos = vector<char> {currentPos[0], static_cast<char>(currentPos[1] + 1)};
            }
            enPableCell = getBoard()->getCell(enPablePos);
        }
        
        Piece *componentEnPable = isEnPableCell(targetCell);
        if (componentEnPable){
            componentEnPable->getCell()->setPiece(nullptr);
            delete componentEnPable;
        }
        


        //check for en passant
        //do we need check all enPablePos??

        //go through the process
        //1. a pawn moves two cells
        //2. the middle cell is set as enpablepos for that pawn
        //3. the previous cell is the target end possition for current pawn
        //4. current pawn moves to that cell, and the pawn is taken
        //6. the enPable Cell is detached.
        
        
        
        delete targetCell->getPiece();
        targetCell->setPiece(this);
        getCell()->setPiece(nullptr);
        setCell(targetCell);
        if (getBoard()->getTurn() != getEnPableTurn()){
            resetEnPable();
        }
        
    } else {
        InvalidMove invalid;
        throw invalid ;
    }
}

void Pawn::promote(Piece *targetPiece){
    getCell()->setPiece(targetPiece);
    delete this;
}

Pawn::~Pawn(){}
