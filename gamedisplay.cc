#include "gamedisplay.h"
#include "board.h"
#include "piece.h"
#include <iostream>
#include "window.h"
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
    if (getGame()->getPlayers().at(0)->getKing()->isChecked())
        cout << "White is in check." << endl;
    if (getGame()->getPlayers().at(1)->getKing()->isChecked())
        cout << "Black is in check." << endl;
        
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

GraphicDisplay::GraphicDisplay(Game *g): Display{g} {}

GraphicDisplay::~GraphicDisplay() {
    delete xw;
}

void GraphicDisplay::display() {
    const int WIDTH = 50;
    const int LEFT_MARGIN = 50;
    const int BOTTOM_MARGIN = 50;
    const int TOP_MARGIN = 50;

    Xwindow w{WIDTH * BOARDSIZE + LEFT_MARGIN * 2, WIDTH * BOARDSIZE + TOP_MARGIN * 2};
    for (int i = 0; i < BOARDSIZE; ++i) {
        for (int j = 0; j < BOARDSIZE; ++j) {
            if (((i + j) % 2) == 0) {
                w.fillRectangle(LEFT_MARGIN + i * WIDTH, TOP_MARGIN + j * WIDTH, WIDTH, WIDTH, Xwindow::White);
            } else {
                w.fillRectangle(LEFT_MARGIN + i * WIDTH, TOP_MARGIN + j * WIDTH, WIDTH, WIDTH, Xwindow::Cyan);
            }
        }
    }

    for (int i = BOARDSIZE; i > 0; --i)
    {
        string row_p = to_string(i);
        w.drawString(LEFT_MARGIN / 2, TOP_MARGIN + WIDTH * (BOARDSIZE - i) + WIDTH / 2, row_p);
        for (int j = 0; j < BOARDSIZE; ++j)
        {
            Piece *p = getGame()->getBoard()->getBoard().at(j).at(i - 1)->getPiece();
            if (p)
            {
                char c = p->getType()[0];
                if (p->getPlayer() == WHITE)
                {
                    c = c + 'A' - 'a'; // capitalize
                    string pp;
                    pp.push_back(c);
                }
                w.drawString(LEFT_MARGIN + WIDTH * (i + 0.5), WIDTH * (i + 0.5) + TOP_MARGIN, pp) 
            }
        }
    }
    for (int i = 0; i < BOARDSIZE; ++i) {
        char c = i + 'a';
		string col_p;
		col_p.push_back(c);
        w.drawString(LEFT_MARGIN + WIDTH * (i + 0.5), TOP_MARGIN + WIDTH * BOARDSIZE + BOTTOM_MARGIN / 2, col_p);
    }

    // might need to add sth later

}




