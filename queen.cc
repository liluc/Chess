#include "queen.h"
#include "piece.h"
#include <vector>
using namespace std;

Queen::Queen(Board *board, Cell *cell, int player):Piece{board, cell, player, "queen"}{}

vector<vector<char>> Queen::possibleMoves(){

}

void Queen::move(vector<char>){
    
}

Queen::~Queen(){}
