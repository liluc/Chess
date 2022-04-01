#include "game.h"
#include "gamedisplay.h"
#include "piece.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

// runGame()
// setUp()
// display()
// undo()
// setpiece(string)
// setTurns(int)
// setWinner(int)
// concludeScore()


int main()
{
    string command;
    Game *game = new Game;
    GameDisplay *textdis = new GameDisplay{game};
    while (cin >> command)
    {
        if (command == "game")
        {
            string white;
            string black;
            cin >> white >> black; // haven't handle the computer AI mode situation
            game->runGame(white, black);
            textdis->display();
        }

        else if (command == "resign")
        {
            int turn = game->getBoard()->getTurn() % 2;
            game->setWinner(turn + 1);
            game->displayScore();
        }

        else if (command == "move")
        {
            string start;
            string end;
            cin >> start >> end; 
            if (start.length() < 2 || end.length() < 2) {
                cerr << "Invalid input" << endl;
                continue;
            }
            vector<char> vStart{start[0], start[1]};
            vector<char> vEnd{end[0], end[1]};
            try {
                game->movePiece(vStart, vEnd);
            } catch (NoPromotion &) {
                string upgrade;
                cin >> upgrade;
                try {
                    game->pawnPromote(vEnd, upgrade);
                } catch (InvalideMove &) {
                    cerr << "Invalid Move command" << endl;
                }
            } catch (InvalidMove &) {
                cerr << "Invalid Move command" << endl;
            }
            textdis->display();
            textdis->displayScore();
        }

        else if (command == "setup")
        {
            string type;
            cin >> type;
            while (type != "done")
            {
                if (type == "+")
                {
                    string piece;
                    string pos;
                    cin >> piece >> pos;
                    vector<char> vPos{pos[0], pos[1]};
                    game->setPiece(piece, vPos);
                }

                else if (type == "-")
                {
                    string pos;
                    cin >> pos;
                    vector<char> vPos{pos[0], pos[1]};
                    game->setPiece("null", vPos);
                }

                // colour should only be black and white for now.
                else if (type == "=")
                {
                    string player;
                    cin >> player;
                    if (player == "white")
                    {
                        game->getBoard()->setTurn(0);
                    }
                    else if (player == "black")
                    {
                        game->getBoard()->setTurn(1);
                    }
                }
                textdis->display();
            }
        }
    }
    cout << "Final Score: " << endl;
    textdis->displayScore();
    delete game;
}