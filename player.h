#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <vector>
#include "game.h"
#include "king.h"

class King;

class Player
{
protected:
    int who;
    float score;
    Game *game;
    King *king;

public:
    Player(int, Game *, float = 0, King * = nullptr);
    virtual ~Player();

    void inc(float);
    void setScore(float);
    void setLevel(int);
    int getLevel() const;
    Game * getGame() const;
    float getScore() const;
    std::vector<Player *> getPlayers() const;
    King *getKing() const;
    void setKing(King *);

    virtual std::vector<std::string> smartMove() = 0;
};

class Human : public Player
{
public:
    Human(int, Game *, float = 0, King * = nullptr);
    ~Human();
    virtual std::vector<std::string> smartMove() override final;
};

class Computer : public Player
{
    int level;

public:
    Computer(int, Game *, int, float = 0, King * = nullptr);
    virtual ~Computer();
    virtual std::vector<std::string> smartMove() = 0;
    int getLevel() const;
};

class Computer_Lv1;
class Computer_Lv2;
class Computer_Lv3;
class Computer_Lv4;
#endif
