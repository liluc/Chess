#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <vector>
#include "king.h"

class King;
class Game;
class Player {
    int who;
    float score;
    Game *g;
    King *king;
    int computer_level;
    public:
    Player(int, int = 0, King * = nullptr);
    ~Player();

    void inc(float);
    void setScore(float);
    void setLevel(int);
    int getLevel() const;
    float getScore() const;
    std::vector<Player *> getPlayers() const;
    King *getKing() const;
};

#endif
