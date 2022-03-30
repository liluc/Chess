#include "game.h"
using namespace std;

const int BOARDSIZE = 8;
const int WHITE = 1;
const int BLACK = 2;
const int DRAW = 3;

Player::Player(int who, int score = 0, bool human = true, King *k = nullptr) who{who} {}

Player::~Player()
{
    delete King;
}

void Player::inc(float x)
{
    score += x;
}

void Player::setscore(float x)
{
    score = x;
}

float Player::getScore() const
{
    return score;
}

void Player::setLevel(int x) const
{
    computer_level = x;
}

int Player::getLevel() const
{
    return computer_level;
}

King *Player::getKing() const
{
    return king;
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

// getters & setters
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

void Game::setWinner(int w)
{
    winner = w;
}

vector<Player *> Game::getPlayers() const
{
    return players;
}

// board builder methods
void Game::fillinPieces()
{
    vector<vector<Cell *>> grid = board->getBoard();
    for (int i = 0; i < BOARDSIZE; ++i)
    {
        Pawn *pawn1 = new Pawn{grid.at(i).at(1), 1};
        Pawn *pawn2 = new Pawn{gird.at(i).at(6), 2};
        board->getPieces().emplace_back(pawn1);
        board->getPieces().emplace_back(pawn2);
        grid.at(i).at(1)->setPiece(pawn1);
        grid.at(i).at(6)->setPiece(pawn2);

        if (i == 0 || i == 7)
        {
            Rook *p1 = new Rook{grid.at(i).at(0), 1};
            Rook *p2 = new Rook{grid.at(i).at(7), 2};
        }
        else if (i == 1 || i == 6)
        {
            Knight *p1 = new Knight{grid.at(i).at(0), 1};
            Knight *p2 = new Knight{grid.at(i).at(7), 2};
        }
        else if (i == 2 || i == 5)
        {
            Bishop *p1 = new Bishop{grid.at(i).at(0), 1};
            Bishop *p2 = new Bishop{grid.at(i).at(7), 2};
        }
        else if (i == 3)
        {
            Queen *p1 = new Queen{grid.at(i).at(0), 1};
            Queen *p2 = new Queen{grid.at(i).at(7), 2};
        }
        else
        {
            King *p1 = new King{grid.at(i).at(0), 1};
            King *p2 = new King{grid.at(i).at(7), 2};
        }
        board->getPieces().emplace_back(p1);
        board->getPieces().emplace_back(p2);
        grid.at(i).at(0)->setPiece(p1);
        grid.at(i).at(7)->setPiece(p2);
    }
}

void Game::rungame(string white, string black)
{
    mode = 1;
    if (white == "computer[1]")
    {
        player[0]->setlevel(1);
    }
    else if (white == "computer[2]")
    {
        player[0]->setlevel(2);
    }
    else if (white == "computer[3]")
    {
        player[0]->setlevel(3);
    }
    else if (white == "computer[4]")
    {
        player[0]->setlevel(4);
    }
    else if (white == "human")
    {
        player[0]->setlevel(0);
    }
    else
    {
        cerr << "Invalid player type for white player!" << endl;
    }
    // for black
    if (black == "computer[1]")
    {
        player[1]->setlevel(1);
    }
    else if (black == "computer[2]")
    {
        player[1]->setlevel(2);
    }
    else if (black == "computer[3]")
    {
        player[1]->setlevel(3);
    }
    else if (black == "computer[4]")
    {
        player[1]->setlevel(4);
    }
    else if (black == "human")
    {
        player[1]->setlevel(0);
    }
    else
    {
        cerr << "Invalid player type for black player!" << endl;
    }

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
            if (piece->getPlayer() == 1)
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
void Game::setPiece(string &p, vector<char> pos)
{
    if (mode != 2)
        cerr << "Invalid command, this command is only valid in set up mode" << endl;
    // function for converting string p to a new Piece
    Cell *curcell = board->getBoard().at(pos[0] - 'a').at(pos[1] - '1');

    if (p == "K")
    {
        King *q = new King(curcell, 1);
    }
    else if (p == "k")
    {
        King *q = new King(curcell, 2);
    }
    else if (p == "Q")
    {
        Queen *q = new Queen(curcell, 1);
    }
    else if (p == "q")
    {
        Queen *q = new Queen(curcell, 2);
    }
    else if (p == "R")
    {
        Rook *q = new Rook(curcell, 1);
    }
    else if (p == "r")
    {
        Rook *q = new Rook(curcell, 2);
    }
    else if (p == "N")
    {
        Knight *q = new Knight(curcell, 1);
    }
    else if (p == "n")
    {
        Knight *q = new Knight(curcell, 2);
    }
    else if (p == "B")
    {
        Bishop *q = new Bishop(curcell, 1);
    }
    else if (p == "b")
    {
        Bishop *q = new Bishop(curcell, 2);
    }
    else if (p == "P")
    {
        Pawn *q = new Pawn(curcell, 1);
    }
    else if (p == "p")
    {
        Pawn *q = new Pawn(curcell, 2);
    }
    board->setPiece(q, pos);
}

void Game::movePiece(vector<char> start, vector<char> end)
{
    if (winner > 0)
        concludeScore();
    if (mode != 1)
        cerr << "Invalid command, this command is only valid in game mode" << endl;

    int curplayer = board->getturn() % 2;

    try
    {
        board.movePiece(start, end);
    }
    catch (Invalidmove &im)
    {
        cerr << "This move is invalid, please check chess rulesheet or seek mental support" << endl;
    }
    if (board->getstate() == true)
    {
        if (players.at(0)->getKing()->ischecked())
        {
            winner = 2;
        }
        else if (player.at(1)->getKing()->ischecked())
        {
            winner = 1;
        }
        else
        {
            winner = 3;
        }
    }
}

void Game::displayScore() const
{
    cout << "Final score:" << endl;
    cout << "White: " << players.at(0)->getscore() << endl;
    cout << "Black: " << players.at(1)->getscore() << endl;
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

ostream &operator<<(ostream &out, const Game &g)
{
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
    return out;
}
