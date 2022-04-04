#ifndef __GAMEDIASPLAY_H_
#define __GAMEDIASPLAY_H_

#include "game.h"
#include "window.h"
#include "observer.h"
#include "subject.h"
// #include "window.h"

class GameDisplay : public Observer {
    Game *g;

    public:
    GameDisplay(Game *);
    Game *getGame() const;
    virtual ~GameDisplay();

    void notify() override;

    virtual void display() = 0;
    void displayScore();
    void displayWinner();
    void displayState();
};

class TextDisplay : public GameDisplay {
    public:
    TextDisplay(Game *);
    ~TextDisplay();

    void display() override;
};

class GraphicDisplay : public GameDisplay {
    Xwindow *xw;
    
    public:
    GraphicDisplay(Game *);
    ~GraphicDisplay();
    void display() override;
};

#endif
