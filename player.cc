#include "player.h"
#include "piece.h"
#include <iostream>
using namespace std;

Player::Player(int who, int score, King *k): who{who} {}

Player::~Player(){ }

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

void Player::setLevel(int x)
{
    computer_level = x;
}

int Player::getLevel() const
{
    return computer_level;
}

King *Player::getKing() const
{
    return king;
}

void Player::setKing(King *k){
    king = k;
}
