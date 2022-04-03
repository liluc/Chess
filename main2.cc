#include "game.h"
#include "gamedisplay.h"
#include "control.h" 
#include "piece.h"
#include "exception.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

int main() {
    string cmd;
    Game *game = new Game;
    Control *gamectrl = new Control{game};
    while (cin >> cmd) {
        if (cmd == "game") {
            // move, resign is part of the game.
            string white;
            string black;
            gamectrl->createPlayer(1, white);
            gamectrl->createPlayer(2, black);

            gamectrl->runGame();
        } else if (cmd == "setup") {
            pieceSetup();
        } else {
            cerr << "Invalid command!" << endl;
        }
    }
}

