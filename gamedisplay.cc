#include "gamedisplay.h"
#include <iostream>


const int BOARDSIZE = 8;
const int WHITE = 1;
const int BLACK = 2;
const int DRAW = 3;

GameDisplay::GameDisplay(Game *game) g{game} {}
GameDisplay::~GameDisplay() {}

void GameDisplay::display() {
    for (int i = BOARDSIZE; i > 0; --i)
    {
        cout << i << " ";
        for (int j = 0; j < BOARDSIZE; ++j)
        {
            Piece *p = g->board->getBoard().at(j).at(i - 1)->getPiece();
            if (p)
            {
                char c = p->getType[0];
                if (p->getPlayer() == WHITE)
                {
                    c = c + 'A' - 'a'; // capitalize
                }
                cout << c << endl; // assuming piece has a method that gets the type, which returns a str
            }
            else
            {
                if ((i + j) % 2 == 0)
                {
                    cout << " ";
                }
                else
                {
                    cout << "_";
                }
            }
        }
        cout << endl;
    }
    cout << endl;
    cout << "  abcdefgh" << endl;
    if (g->players.at(0)->getKing()->ischecked())
        cout << "White is in check." << endl;
    if (g->players.at(1)->getKing()->ischecked())
        cout << "Black is in check." << endl;
    if (g->players.at(0)->getKing()->ischeckmate() ||
        g->players.at(1)->getKing()->ischeckmate())
        cout << "Checkmate! ";

    // by separating "checkmate!" and "... wins", we can account for the case of resignation
    if (winner == DRAW)
    {
        cout << "Stalemate" << endl;
    }
    else if (winner == WHITE)
    {
        cout << "White wins!" << endl;
    }
    else if (winner == BLACK)
    {
        cout << "Black wins!" << endl;
    }
}

void displayScore()
{
    if (g->getWinner() != 0)
        return;
    int whiteScore = g->getPlayers()[0]->getscore();
    int blackScore = g->getPlayers()[1]->getscore();
    cout << "White Score: " << whiteScore << endl;
    cout << "Black Score: " << blackScore << endl;
}
