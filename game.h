#include "board.h"
#include <vector>
#include <iostream>
#include "player.h"
#include "king.h"

class History;

// Game will serve as an interface to the board, as well as maintaining certain client-side data(like scores)
class Game
{
    int mode;
    int winner;
    std::vector<Player *> players;
    Board *board;
    History *hist;

public:
    Game();
    ~Game();
    // rungame() and setup() invokes the dtor for old board and call ctor() for board and game, and set gamemode
    void runGame(std::string, std::string);
    void fillinPieces();
    void setup();
    void exitsetup();

    // getters
    Board *getBoard() const;
    std::vector<Player *> getPlayers() const;
    int getMode() const;
    History *getHist() const;
    int getWinner() const;
    void setWinner(int);

    // shells for invoking Board methods
    void setPiece(const std::string &, std::vector<char>);
    void movePiece(std::vector<char>, std::vector<char>);

    friend std::ostream operator<<(std::ostream &, const Game *);

    void concludeScore() const;
    void displayScore() const;

    // additional features
    void undo();
};
