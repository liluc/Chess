#include "game.h"

Class GameDisplay {
    Game *g;

    public:
    BoardDisplay(Game *);
    ~BoardDisplay();
    display();
    displayScore();
    // display_graphic();
}