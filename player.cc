Player::Player(int who, int score = 0, bool human = true, King *k = nullptr) who{who} {}

Player::~Player()
{
    delete King;
}

void Player::inc(float x)
{
    score += x;
}

void Player::setscore(float x)
{
    score = x;
}

float Player::getScore() const
{
    return score;
}

void Player::setLevel(int x) const
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