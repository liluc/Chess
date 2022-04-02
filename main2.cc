#include "game.h"
#include "gamedisplay.h"
#include ""
#include "piece.h"
#include "exception.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

int main() {
    string cmd;
    Game *game = new Game;
    TextDisplay *textdis = new TextDisplay{game};
    Control *gamectrl = new Control{game};
    while (cin >> cmd) {
        if (cmd == "game") {
            string white;
            string black;
            gamectrl->createPlayer(1, white);
            gamectrl->createPlayer(2, black);
            gamectrl->runGame();
            }
    }
}