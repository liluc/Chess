#include "player.h"

Player::Player(int who, int score, King *k): who{who} {}

Player::~Player()
{
    delete king;
}

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