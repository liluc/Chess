#include "gamedisplay.h"
#include "board.h"
#include "piece.h"
#include <iostream>
using namespace std;


const int BOARDSIZE = 8;
const int WHITE = 1;
const int BLACK = 2;
const int DRAW = 3;

// Display has-a Game
Display::Display(Game *game): g{game} {
    game->getBoard()->attach(this);
}
Display::~Display() {
    g->getBoard()->detach(this);
}

Game * Display::getGame() const{
    return g;
}

void Display::notify() {
    display();
    display();
}

void Display::displayScore()
{
    if (g->getWinner() != 0)
        return;
    int whiteScore = g->getPlayers()[0]->getScore();
    int blackScore = g->getPlayers()[1]->getScore();
    cout << "White Score: " << whiteScore << endl;
    cout << "Black Score: " << blackScore << endl;
}

// just use super class ctor and dtor
TextDisplay::TextDisplay(Game * g) : Display{g}{}

TextDisplay::~TextDisplay() {}

void TextDisplay::display() {
    for (int i = BOARDSIZE; i > 0; --i)
    {
        cout << i << " ";
        for (int j = 0; j < BOARDSIZE; ++j)
        {
            Piece *p = getGame()->getBoard()->getBoard().at(j).at(i - 1)->getPiece();
            if (p)
            {
                char c = p->getType()[0];
                if (p->getPlayer() == WHITE)
                {
                    c = c + 'A' - 'a'; // capitalize
                }
                cout << c; // assuming piece has a method that gets the type, which returns a str
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

    if (getGame()->getPlayers().at(0)->getKing()->isChecked())
        cout << "White is in check." << endl;
    if (getGame()->getPlayers().at(1)->getKing()->isChecked())
        cout << "Black is in check." << endl;
        
    // cout << "isChecked pass" << endl;

    if (getGame()->isCheckmate())
        cout << "Checkmate! ";

    // by separating "checkmate!" and "... wins", we can account for the case of resignation
    if (getGame()->isStalemate())
    {
        cout << "Stalemate!" << endl << "The game ends in a tie" << endl;
    }
    else if (getGame()->getWinner() == WHITE)
    {
        cout << "White wins!" << endl;
    }
    else if (getGame()->getWinner() == BLACK)
    {
        cout << "Black wins!" << endl;
    }
}

GraphicDisplay::GraphicDisplay(Game *g): Display{g}{}

GraphicDisplay::~GraphicDisplay() {}

// GraphicDisplay::display() {}




