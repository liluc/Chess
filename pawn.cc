#include "pawn.h"
#include <vector>
using namespace std;

Pawn::Pawn(Board *board, Cell *cell, int player):Piece{board, cell, player, "pawn"}, steps{0} {}

    // std::vector<std::vector<char>> possibleMoves() override;
    // void move(std::vector<char>) override;
    // void promote();
    // ~Pawn();
vector<vector<char>> Pawn::possibleMoves(){

}

void Pawn::move(vector<char>){
    
}

void Pawn::promote(){

}

Pawn::~Pawn(){}
