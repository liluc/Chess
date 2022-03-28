#include "game.h"

Player::Player(int who, int score = 0, bool human = true, King *k = nullptr) who{who} {}

Player::~Player()
{
    delete King;
}

Game::Game()
{
    Board newboard = new Board();
    board = newboard;
    added_players = vector<Players>;
    Player *new_player1 = new Player{1};
    Player *new_player2 = new Player{2};
    added_players.emplace_back(new_player1);
    added_players.emplace_back(new_player2);
    players = added_players;

    History newhist = new History();
    hist = newhist;
    mode = 0;
}

Game::~Game()
{
    delete board;
    delete history;
    for (auto player ::players)
    {
        delete player;
    }
}

// getters
Board *Game::getBoard() const
{
    return board;
}

vector<Player *> Game::getPlayers() const
{
    return players;
}

int Game::getMode() const
{
    return mode;
}

History *Game::getMode() const
{
    return hist;
}

int Game::getWinner() const
{
    return winner;
}

// board builder methods
void Game::fillinPieces();

void Game::rungame()
{
    mode = 1;
    if (board->getPieces().size() == 0)
        fillinPieces();

    // fillin the pieces
}

void Game::setup()
{
    mode = 2;
    delete board;
    delete hist;

    Board newboard = new Board();
    board = newboard;
    History newhist = new History();
    hist = newhist;
}

void Game::exitsetup()
{
    if (mode != 2)
    {
        return;
    }
    bool white_king{false};
    bool black_king{false};
    bool no_pawn_promoted{true};

    for (auto piece : board->getPieces())
    {
        if (piece->gettype() == "Pawn")
        {
            if (piece->getplayer() == 1)
            {
                no_pawn_promoted = no_pawn_promoted && (piece->cell->getpos().at(1) == 8);
            }
            else
            {
                no_pawn_promoted = no_pawn_promoted && (piece->cell->getpos().at(1) == 1;)
            }
        }
        else if (piece->gettype() == "King")
        {
            if (piece->getplayer() == 1)
            {
                white_king = true;
            }
            else
            {
                black_king = true;
            }
        }
    }

    bool ret = white_king && black_king && (!white_king.ischecked()) && (!black_king.ischecked()) && no_pawn_promoted;

    if (!ret)
    {
        cerr << "Invalid board set up, cannot exit set up mode." << endl;
    }
    else
    {
        mode = 0;
    }
}

// incomplete
Game::setPiece(string &p, vector<char> pos)
{
    if (mode != 2)
        cerr << "Invalid command, this command is only valid in set up mode" << endl;
    // function for converting string p to a new Piece
    p = new Piece();
    board.setPiece(p, pos);
}

Game::movePiece(vector<char> start, vector<char> end)
{
    if (winner > 0)
        concludeScore();
    if (mode != 1)
        cerr << "Invalid command, this command is only valid in game mode" << endl;
    board.movePiece(start, end);
    if (board->getstate() == true)
    {
        if (players.at(0)->king->ischecked())
        {
            winner = 2;
        }
        else if (player.at(1)->king->ischecked())
        {
            winner = 1;
        }
        else
        {
            winner = 3;
        }
    }
}

void Game::concludeScore()
{
    if (winner == 0)
        return;
    if (winner == 1)
        players.at(0)->inc(1);
    if (winner == 2)
        players.at(1)->inc(1);
    if (winner == 3)
    {
        players.at(0)->inc(0.5);
        players.at(1)->inc(0.5);
    }
    return;
}
