#ifndef __GAMEDIASPLAY_H_
#define __GAMEDIASPLAY_H_

#include "game.h"

class GameDisplay {
    Game *g;

    public:
    GameDisplay(Game *);
    ~GameDisplay();
    void display();
    void displayScore();
    // display_graphic();
};

#endif
