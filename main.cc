#include "game.h"
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

// I wrote a displayScore in Game so we don't have to do it here

void displayScore(Game *game)
{
    if (game->getWinner() != 0)
        return;
    // cout << "Final Score:" << endl;
    int whiteScore = game->getPlayers()[0]->getscore();
    int blackScore = game->getPlayers()[1]->getscore();
    cout << "White Score: " << whiteScore << endl;
    cout << "Black Score: " << blackScore << endl;
}

int main()
{
    string command;
    Game *game = new Game;
    while (cin >> command)
    {
        if (command == "game")
        {
            string white;
            string black;
            cin >> white >> black; // haven't handle the computer AI mode situation
            game->runGame(white, black);
            cout << game;
        }

        else if (command == "resign")
        {
            int turn = game->getBoard()->getTurn() % 2;
            game->setWinner(turn + 1);
            displayScore(game);
        }

        else if (command == "move")
        {
            string start;
            string end;
            cin >> start; 
            vector<char> vStart{start[0], start[1]};
            vector<char> vEnd{end[0], end[1]};
            game->movePiece(vStart, vEnd);
            cout << game;
            displayScore(game);
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
                cout << game;
            }
        }
    }
    cout << "Final Score: " << endl;
    game->displayScore();
    delete game;
}