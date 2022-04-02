#ifndef __CONTROL_H__
#define __CONTROL_H__

#include "game.h"
#include "gamedisplay.h"
#include <vector>
#include <string>

class Control {
    Game *g;
    TextDisplay *td;
    GraphicDisplay *gd;

    public:
    Control(Game *);
    ~Control();
    void createPlayer(int, const std::string &);
    void runGame();
    void pieceSetup();
};
