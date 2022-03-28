#include "piece.h"
#include "cell.h"
#include "board.h"
#include <vector>
using namespace std;

Piece::Piece(Board *board, Cell *cell, int player):board{board}, cell{cell}, player{player}{}

vector<char> Piece::getPos(){
    return cell->getPos();
}

Cell * Piece::getcell(){
    return cell;
}

Board * Piece::getBoard(){
    return Board;
}

int Piece::getPlayer(){
    return player;
}

//pos must have two entries only!!!!
bool Piece::contained(vector<vector<char>> posList, vector<char> pos){
    for (auto x : posList){
        if (x[0] != pos[0] || x[1] != pos[1]) return false;
    }
    return true;
}

Piece::~Piece(){};
