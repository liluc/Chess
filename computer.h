#ifndef __COMPUTER_H__
#define __COMPUTER_H__

#include "player.h"

class Computer_Lv1 {
    public:
    Computer_Lv1();
    ~Computer_Lv1();
    std::vector<std::string> smartMove() override final;
};

class Computer_Lv2 {
    public:
    Computer_Lv2();
    ~Computer_Lv2();
    std::vector<std::string> smartMove() override final;
};

class Computer_Lv3 {
    public:
    Computer_Lv3();
    ~Computer_Lv3();
    std::vector<std::string> smartMove() override final;
};

class Computer_Lv4 {
    public:
    Computer_Lv4();
    ~Computer_Lv4();
    std::vector<std::string> smartMove() override final;
};