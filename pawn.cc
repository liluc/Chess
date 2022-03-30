#include "pawn.h"
#include <vector>
using namespace std;

Pawn::Pawn(Cell *cell, int player, int steps):Piece{cell, player}, steps{steps}{}

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
