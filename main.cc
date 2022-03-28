#include "game.h"
#include "piece.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

//runGame()
//setUp()
//display()
//undo()
//setpiece(string)
//setTurns(int)
//setWinner(int)
//concludeScore()

void displaySore(Game *game){
    cout << "Final Score:" << endl;
    int whiteScore = game->getPalyer()[0]->getScore();
    int blackScore = game->getPalyer()[1]->getScore();
    cout << "White Score: " << whiteScore << endl;
    cout << "Black Score: " << blackScore << endl;
}

int main(){
    string command;
    Game *game = new Game;
    while (cin >> command){
        if (command == "game"){ 
            string white;
            string black;
            cin >> white >> black; // haven't handle the computer AI mode situation
            game.runGame();
            game.display();
        }

        else if (command == "resign"){
            int turn = game->getBoard()->getTurn() % 2;
            setWinner (turn + 1);
        }

        else if (command == "move"){
            string start;
            string end;
            cin >> start >> endl;
            vector<char> vStart {start[0], start[1]};
            vector<char> vEnd {end[0], end[1]};
            game.movePiece(vStart, vEnd);
            game.display();
        }

        else if (command == "setup"){
            string type;
            cin >> type;
            while (type != "done"){
                if (type == "+"){
                    string piece;
                    string pos;
                    cin >> piece >> pos;
                    vector<char> vPos {pos[0], pos[1]};
                    game.setPiece(piece, vPos);
                }

                else if (type == "-"){
                    string pos;
                    cin >> pos;
                    vector<char> vPos {pos[0], pos[1]};
                    game.setPiece("", vPos);
                }

                //colour should only be black and white for now.
                else if (type == "="){
                    string player;
                    cin >> player;
                    if (player == "white"){
                        game.setTurns(1);
                    } else if (player == "black"){
                        game.setTurns(2);
                    }
                }
                
            }
        }
    }
    displaySore(game);
    delete game;
}