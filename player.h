#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <vector>
#include "king.h"

class King;

class Player {
    int who;
    float score;
    int computer_level; // 0 if human
    King *king;

    public:
    Player(int, int = 0, bool = true, King * = nullptr);
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
