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
void Game::setPiece(string &p, vector<char> pos)
{
    if (mode != 2)
        cerr << "Invalid command, this command is only valid in set up mode" << endl;
    // function for converting string p to a new Piece
    p = new Piece();
    board.setPiece(p, pos);
}

void Game::movePiece(vector<char> start, vector<char> end)
{
    if (winner > 0)
        concludeScore();
    if (mode != 1)
        cerr << "Invalid command, this command is only valid in game mode" << endl;
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