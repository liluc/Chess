#include "board.h"
#include <vector>
#include <iostream>

class Player
{
    int who;
    float score;
    bool human;
    King *king;

public:
    Player();
    ~Player();

    void inc(float);
    void setscore(float);
    int getscore() const;
}

class Game
{
    int mode;
    int winner;
    vector<Player *> players;
    Board *board;
    History *hist;

public:
    Game();
    ~Game();
    // rungame() and setup() invokes the dtor for old board and call ctor() for board and game, and set gamemode
    void rungame();
    void fillinPieces();
    void setup();
    void exitsetup();

    // getters
    Board *getBoard() const;
    vector<Player *> getPlayers() const;
    int getMode() const;
    History *getHist() const;
    int getWinner() const;

    // shells for invoking Board methods
    void setPiece(string &, vector<char>);
    void movePiece(vector<char>, vector<char>);

    friend std::ostream operator<<(std::ostream &, const Game &);

    void concludeScore() const;
    //
    // additional features
    void undo();
}
