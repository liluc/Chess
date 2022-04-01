#include "king.h"
#include "piece.h"
#include "board.h"
#include <vector>
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

bool King::isChecked() const{
    //tranverse the board
    //check every piece
    //if it is a piece of component, then check its possible moves, if this cell is contained, return true;
    vector<vector<Cell *>> board= getBoard()->getBoard();
    for(auto col : board){
        for(auto cell : col){
            if (!cell->getPiece()){
                Piece *piece = cell->getPiece();
                if (piece->getPlayer() != getPlayer()){
                    vector<vector<char>> moves = cell->getPiece()->possibleMoves();
                    if (contained(moves, getPos())) return true;
                }
            }
        }
    }
    return false;
}

// bool King::isCheckMate() const {
//     return isChecked() && getBoard()->isStalemate();
// }

King::~King(){}
