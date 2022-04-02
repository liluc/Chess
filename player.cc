#include "player.h"

Player::Player(int who, int score, Piece *k): who{who} {}

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

Human::Human(int who, int score, Piece *king): Player{who, score, king} {}

Human::~Human() {}

vector<string> Human::smartMove() {
    vector<string> retstr{"no_suggestions"};
    return retstr;
}

Computer::Computer() {int who, int level, int score, Piece *king): Player{who, score, king}, level{level} {}

Computer::~Computer() {}

int Computer::getLevel() {
    return level;
}

// computer's smartMove is pure virtual
