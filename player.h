#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <vector>
#include "game.h"
#include "king.h"

class King;

class Player {
    int who;
    float score;
    Game * game;
    Piece * king;

    public:
    Player(int, Game *, int = 0, Piece * = nullptr);
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
    Human(int, Game * int = 0, Piece * = nullptr);
    ~Human();
    virtual std::vector<std::string> smartMove() override final;
};

class Computer : public Player {
    int level;
    public:
    Computer(int, Game *, int, int = 0, Piece * = nullptr);
    ~Computer();
    virtual std::vector<std::string> smartMove() override = 0;
    int getLevel();
};

#endif
