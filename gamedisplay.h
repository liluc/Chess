#ifndef __GAMEDIASPLAY_H_
#define __GAMEDIASPLAY_H_

#include "game.h"
#include "observer.h"
#include "subject.h"

class Display : public Observer {
    Game *g;

    public:
    Display(Game *);
    Game *getGame() const;
    virtual ~Display();

    void notify() override;

    virtual void display() = 0;
    void displayScore();
};

class TextDisplay : public Display {
    public:
    TextDisplay(Game *);
    ~TextDisplay();

    void display() override;
};

class GraphicDisplay : public Display {
    public:
    GraphicDisplay(Game *);
    ~GraphicDisplay();

    void display() override;
};

#endif
