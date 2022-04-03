#include "player.h"
#include "piece.h"
#include <iostream>
using namespace std;

Player::Player(int who, Game *g, int score, King *k) : who{who}, game{g} {}

Player::~Player() {} // no need to delete board and king because player doesn't own them

void Player::inc(float x)
{
    score += x;
}

void Player::setScore(float x)
{
    score = x;
}

float Player::getScore() const
{
    return score;
}

int Computer::getLevel() const
{
    return level;
}

King *Player::getKing() const
{
    return king;
}

Game * Player::getGame() const {
    return game;
}

void Player::setKing(King * k) {
    king = k;
}

Human::Human(int who, Game *g, int score, King *king) : Player{who, g, score, king} {}

Human::~Human() {}

vector<string> Human::smartMove()
{
    vector<string> retstr{"no_suggestions"};
    return retstr;
}

Computer::Computer(int who, Game *g, int level, int score, King *king): Player{who, g, score, king}, level{level} {}

Computer::~Computer() {}

// computer's smartMove is pure virtual
