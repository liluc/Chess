#ifndef __COMPUTER_H__
#define __COMPUTER_H__

#include "player.h"
#include <vector>
#include <string>

class Computer_Lv1 : public Computer {
    public:
    Computer_Lv1(int, Game *, int, float = 0, King * = nullptr);
    ~Computer_Lv1();
    virtual std::vector<std::string> smartMove() override final;
};

class Computer_Lv2 : public Computer {
    public:
    Computer_Lv2(int, Game *, int, float = 0, King * = nullptr);
    ~Computer_Lv2();
    virtual std::vector<std::string> smartMove() override final;
};

class Computer_Lv3 : public Computer {
    public:
    Computer_Lv3(int, Game *, int, float = 0, King * = nullptr);
    ~Computer_Lv3();
    virtual std::vector<std::string> smartMove() override final;
};


class Computer_Lv4 : public Computer {
    public:
    Computer_Lv4(int, Game *, int, float = 0, King * = nullptr);
    ~Computer_Lv4();
    virtual std::vector<std::string> smartMove() override final;
};

#endif
