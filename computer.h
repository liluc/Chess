#ifndef __COMPUTER_H__
#define __COMPUTER_H__

#include "player.h"
#include <vector>
#include <string>

class Computer_Lv1 {
    public:
    Computer_Lv1(int, Board *, int, int, King *);
    ~Computer_Lv1();
    std::vector<std::string> smartMove() override final;
};

class Computer_Lv2 {
    public:
    Computer_Lv2(int, Board *, int, int, King *);
    ~Computer_Lv2();
    std::vector<std::string> smartMove() override final;
};

class Computer_Lv3 {
    public:
    Computer_Lv3(int, Board *, int, int, King *);
    ~Computer_Lv3();
    std::vector<std::string> smartMove() override final;
};

class Computer_Lv4 {
    public:
    Computer_Lv4(int, Board *, int, int, King *);
    ~Computer_Lv4();
    std::vector<std::string> smartMove() override final;
};

