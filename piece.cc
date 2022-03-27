#include "piece.h"
#include <vector>

Piece::Piece(Cell *cell, int player):cell{cell}, player{player}{}

Piece::~Piece(){};
