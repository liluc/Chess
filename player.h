#include <vector>
#include "king.h"

class King;

class Player
{
    int who;
    float score;
    int computer_level; // 0 if human
    King *king;

public:
    Player();
    ~Player();

    void inc(float);
    void setscore(float);
    void setlevel(int);
    int getlevel() const;
    int getscore() const;
    std::vector<Player *> getplayers() const;
    King *getKing() const;
};