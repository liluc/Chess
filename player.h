#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <vector>
#include "king.h"

class King;

class Player {
    int who;
    float score;
    Board * b;
    Piece * king;

    public:
    Player(int, int = 0, Piece * = nullptr);
    ~Player();

    void inc(float);
    void setScore(float);
    void setLevel(int);
    int getLevel() const;
    float getScore() const;
    std::vector<Player *> getPlayers() const;
    Piece *getKing() const;
    
    virtual std::vector<std::string> smartMove() = 0;
};

class Human : public Player {
    public:
    Human(int, int = 0, Piece * = nullptr);
    ~Human();
    virtual std::vector<std::string> smartMove() override final;
};

class Computer : public Player {
    int level;
    public:
    Computer(int, int = 0, Piece * = nullptr);
    ~Computer();
    virtual std::vector<std::string> smartMove() override = 0;
    int getLevel();
};

#endif
