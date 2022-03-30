#include "board.h"
#include <vector>
#include <iostream>

class King;
class Player
{
    int who;
    float score;
    int computer_level; // 0 if human
    King *king;

public:
    Player();
    ~Player();

    void inc(float);
    void setscore(float);
    void setlevel(int);
    int getlevel() const;
    int getscore() const;
    vector<Player *> getplayers() const;
    King *getKing() const;
}

// Game will serve as an interface to the board, as well as maintaining certain client-side data(like scores)
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
    void rungame(string, string);
    void fillinPieces();
    void setup();
    void exitsetup();

    // getters
    Board *getBoard() const;
    vector<Player *> getPlayers() const;
    int getMode() const;
    History *getHist() const;
    int getWinner() const;
    void setWinner();

    // shells for invoking Board methods
    void setPiece(string &, vector<char>);
    void movePiece(vector<char>, vector<char>);

    friend std::ostream operator<<(std::ostream &, const Game &);

    void concludeScore() const;
    void displayScore() const;

    // additional features
    void undo();
}
