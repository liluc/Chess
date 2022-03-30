#include "king.h"
#include "piece.h"
#include <vector>
using namespace std;

King::King(Board * board, Cell *cell, int player):Piece{board, cell, player, "king"}{}

vector<vector<char>> King::possibleMoves(){

}

void King::move(vector<char>){
    
}

King::~King(){}
