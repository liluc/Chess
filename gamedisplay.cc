#include "gamedisplay.h"
#include <iostream>


const int BOARDSIZE = 8;
const int WHITE = 1;
const int BLACK = 2;
const int DRAW = 3;

// Display has-a Game
Display::Display(Game *game): g{game} {
    game->getBoard()->attach(this);
}
Display::~Display() {
    game->getBoard()->detach(this);
}

void Display::notify() {
    display();
    display()
}

void Display::displayScore()
{
    if (g->getWinner() != 0)
        return;
    int whiteScore = g->getPlayers()[0]->getscore();
    int blackScore = g->getPlayers()[1]->getscore();
    cout << "White Score: " << whiteScore << endl;
    cout << "Black Score: " << blackScore << endl;
}

// just use super class ctor and dtor
TextDisplay::TextDisplay() {}

TextDisplay::~TextDisplay() {}

void TextDisplay::display() {
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
    if (g->isCheckmate())
        cout << "Checkmate! ";

    // by separating "checkmate!" and "... wins", we can account for the case of resignation
    if (g->isStalemate())
    {
        cout << "Stalemate!" << endl << "The game ends in a tie" << endl;
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

GraphicDisplay::GraphicDisplay() {}

GraphicDisplay::~GraphicDisplay() {}

// GraphicDisplay::display() {}


