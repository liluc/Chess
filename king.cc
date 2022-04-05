#include "king.h"
#include "piece.h"
#include "board.h"
#include <vector>
#include <iostream>
using namespace std;

King::King(Board * board, Cell *cell, int player):Piece{board, cell, player, "king"}{}


vector<vector<char>> King::possibleMoves(){
    vector<vector<char>> cells;
    addCell(1, 0, cells);
    addCell(-1, 0, cells);
    addCell(0, 1, cells);
    addCell(0, -1, cells);
    addCell(1, 1, cells);
    addCell(1, -1, cells);
    addCell(-1, 1, cells);
    addCell(-1, -1, cells);
    
    return cells;
}

vector<char> createPos (vector<char> v, int colInc, int rowInc){
    char newCol = v[0] + colInc;
    char newRow = v[1] + rowInc;
    vector<char> newPos {newCol, newRow};
    return newPos;
}

//1 : piece of the same player
//2 : wanted piece of the other player
//3 : no piece at the cell
//4 : pos out of bound;
int King::existPiece(vector<char> pos, int colInc, int rowInc, string type) const{
    vector<char> targetPos = createPos(pos, colInc, rowInc);
    if (checkBound(targetPos)){
        Piece *targetPiece = getBoard()->getCell(targetPos)->getPiece();
        if (targetPiece){
            if (targetPiece->getPlayer() == getPlayer()) return 1;
            if (targetPiece->getType() == type) return 2;
        }
        return 3;
    }
    return 4;
}

bool King::isChecked() const{
    //tranverse the board
    //check every piece
    //if it is a piece of component, then check its possible moves, if this cell is contained, return true;
    vector<vector<Cell *>> board= getBoard()->getBoard();
    // cout << getPlayer() << endl;
    
    //check all side of the king, check if the first piece in the bound is the piece of the other player
    vector<char> kingPos = getPos();

    //check rook and queen;
    for (int colInc = 1; colInc < 8; ++colInc){ //horizontal move right
        int checkRook = existPiece(kingPos, colInc, 0, "rook");
        int checkQueen = existPiece(kingPos, colInc, 0, "queen");
        if (checkRook == 1) break; //there is a piece of current player
        if (checkRook == 2 || checkQueen == 2) return true;
    }
    for (int colInc = -1; colInc > -8; --colInc){ //horizontal move left
        int checkRook = existPiece(kingPos, colInc, 0, "rook");
        int checkQueen = existPiece(kingPos, colInc, 0, "queen");
        if (checkRook == 1) break;
        if (checkRook == 2 || checkQueen == 2) return true;
    }
    for (int rowInc = 1; rowInc < 8; ++rowInc){ //vertical move up
        int checkRook = existPiece(kingPos, 0, rowInc, "rook");
        int checkQueen = existPiece(kingPos, 0, rowInc, "queen");
        if (checkRook == 1) break;
        if (checkRook == 2 || checkQueen == 2) return true;
    }
    for (int rowInc = -1; rowInc > -8; --rowInc){ //vertical move down
        int checkRook = existPiece(kingPos, 0, rowInc, "rook");
        int checkQueen = existPiece(kingPos, 0, rowInc, "queen");
        if (checkRook == 1) break;
        if (checkRook == 2 || checkQueen == 2) return true;
    }


    //check bishop and queen
    for (int col = 1, row = 1; col < 8, row < 8; ++col, ++row){ // move towards top right
        int checkBishop = existPiece(kingPos, col, row, "bishop");
        int checkQueen = existPiece(kingPos, col, row, "queen");
        if (checkBishop == 1) break;
        if (checkBishop == 2 || checkQueen == 2) return true;
    }
    for (int col = -1, row = 1; col > -8, row < 8; --col, ++row){ // move towards top left
        int checkBishop = existPiece(kingPos, col, row, "bishop");
        int checkQueen = existPiece(kingPos, col, row, "queen");
        if (checkBishop == 1) break;
        if (checkBishop == 2 || checkQueen == 2) return true;
    }
    for (int col = 1, row = -1; col < 8, row > -8; ++col, --row){ // move towards down right
        int checkBishop = existPiece(kingPos, col, row, "bishop");
        int checkQueen = existPiece(kingPos, col, row, "queen");
        if (checkBishop == 1) break;
        if (checkBishop == 2 || checkQueen == 2) return true;
    }
    for (int col = -1, row = -1; col > -8, row > -8; --col, --row){ // move towards down left       
        int checkBishop = existPiece(kingPos, col, row, "bishop");
        int checkQueen = existPiece(kingPos, col, row, "queen");
        if (checkBishop == 1) break;
        if (checkBishop == 2 || checkQueen == 2) return true;
    }


    //check knight
    if (existPiece(kingPos, 1, 2, "night") == 2) return true;
    if (existPiece(kingPos, 2, 1, "night") == 2) return true;
    if (existPiece(kingPos, -1, 2, "night") == 2) return true;
    if (existPiece(kingPos, -2, 1, "night") == 2) return true;
    if (existPiece(kingPos, 1, -2, "night") == 2) return true;
    if (existPiece(kingPos, 2, -1, "night") == 2) return true;
    if (existPiece(kingPos, -1, -2, "night") == 2) return true;
    if (existPiece(kingPos, -2, -1, "night") == 2) return true;

    //check pawn
    if (getPlayer() == 1){
        if (existPiece(kingPos, -1, 1, "pawn") == 2) return true;
        if (existPiece(kingPos, 1, 1, "pawn") == 2) return true;
    } 
    else if (getPlayer() == 2){
        if (existPiece(kingPos, 1, -1, "pawn") == 2) return true;
        if (existPiece(kingPos, -1, -1, "pawn") == 2) return true;
    }

    return false;
}

// bool King::isCheckMate() const {
//     return isChecked() && getBoard()->isStalemate();
// }

King::~King(){}
