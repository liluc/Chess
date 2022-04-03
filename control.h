#ifndef __CONTROL_H__
#define __CONTROL_H__

#include "game.h"
#include "gamedisplay.h"
#include "player.h"
#include "computer.h"
#include <vector>
#include <string>

class Control {
    Game *game;
    TextDisplay *td;
    GraphicDisplay *gd;

    public:
    Control(Game *);
    ~Control();
    Game * getGame() const;
    
    void createPlayer(int, const std::string &);

    void runGame(std::string, std::string);
    void makeMove(int);   // makeMove() is a helper method
    
    void pieceSetup();
};

#endif
