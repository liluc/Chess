#include "game.h"
using namespace std;


Game::Game()
{
    Board * newboard = new Board();
    board = newboard;
    vector<Player *> added_players;
    Player *new_player1 = new Player{1};
    Player *new_player2 = new Player{2};
    added_players.emplace_back(new_player1);
    added_players.emplace_back(new_player2);
    players = added_players;

    History *newhist = new History();
    hist = newhist;
    mode = 0;
}

Game::~Game()
{
    delete board;
    delete hist;
    for (auto player : players)
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

History *Game::getHist() const
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
    const int BOARDSIZE = 8;
    vector<vector<Cell *>> grid = board->getBoard();
    for (int i = 0; i < BOARDSIZE; ++i)
    {
        Pawn *pawn1 = new Pawn{board, grid.at(i).at(1), 1};
        Pawn *pawn2 = new Pawn{board, gird.at(i).at(6), 2};
        board->getPieces().emplace_back(pawn1);
        board->getPieces().emplace_back(pawn2);
        grid.at(i).at(1)->setPiece(pawn1);
        grid.at(i).at(6)->setPiece(pawn2);

        if (i == 0 || i == 7)
        {
            Rook *p1 = new Rook{board, grid.at(i).at(0), 1};
            Rook *p2 = new Rook{board, grid.at(i).at(7), 2};
        }
        else if (i == 1 || i == 6)
        {
            Knight *p1 = new Knight{board, grid.at(i).at(0), 1};
            Knight *p2 = new Knight{board, grid.at(i).at(7), 2};
        }
        else if (i == 2 || i == 5)
        {
            Bishop *p1 = new Bishop{board, grid.at(i).at(0), 1};
            Bishop *p2 = new Bishop{board, grid.at(i).at(7), 2};
        }
        else if (i == 3)
        {
            Queen *p1 = new Queen{borad, grid.at(i).at(0), 1};
            Queen *p2 = new Queen{borad, grid.at(i).at(7), 2};
        }
        else
        {
            King *p1 = new King{board, grid.at(i).at(0), 1};
            King *p2 = new King{borad, grid.at(i).at(7), 2};
        }
        board->getPieces().emplace_back(p1);
        board->getPieces().emplace_back(p2);
        grid.at(i).at(0)->setPiece(p1);
        grid.at(i).at(7)->setPiece(p2);
    }
}

void Game::runGame(string white, string black)
{
    mode = 1;
    if (white == "computer[1]")
    {
        players[0]->setlevel(1);
    }
    else if (white == "computer[2]")
    {
        players[0]->setlevel(2);
    }
    else if (white == "computer[3]")
    {
        players[0]->setlevel(3);
    }
    else if (white == "computer[4]")
    {
        players[0]->setlevel(4);
    }
    else if (white == "human")
    {
        players[0]->setlevel(0);
    }
    else
    {
        cerr << "Invalid player type for white player!" << endl;
    }
    // for black
    if (black == "computer[1]")
    {
        players[1]->setlevel(1);
    }
    else if (black == "computer[2]")
    {
        players[1]->setlevel(2);
    }
    else if (black == "computer[3]")
    {
        players[1]->setlevel(3);
    }
    else if (black == "computer[4]")
    {
        player[1]->setlevel(4);
    }
    else if (black == "human")
    {
        players[1]->setlevel(0);
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
        if (piece->getType() == "Pawn")
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

// helper function to turn string input to a corresponding piece and throw exception if 
Piece * stringtoPiece(Board * b, const string &p, vector<char> pos) {
    Cell *curcell = b->getBoard().at(pos[0] - 'a').at(pos[1] - '1');
    if (p == "K")
    {
        King *q = new King(b, curcell, 1);
    }
    else if (p == "k")
    {
        King *q = new King(b, curcell, 2);
    }
    else if (p == "Q")
    {
        Queen *q = new Queen(b, curcell, 1);
    }
    else if (p == "q")
    {
        Queen *q = new Queen(b, curcell, 2);
    }
    else if (p == "R")
    {
        Rook *q = new Rook(b, curcell, 1);
    }
    else if (p == "r")
    {
        Rook *q = new Rook(b, curcell, 2);
    }
    else if (p == "N")
    {
        Knight *q = new Knight(b, curcell, 1);
    }
    else if (p == "n")
    {
        Knight *q = new Knight(b, curcell, 2);
    }
    else if (p == "B")
    {
        Bishop *q = new Bishop(b, curcell, 1);
    }
    else if (p == "b")
    {
        Bishop *q = new Bishop(b, curcell, 2);
    }
    else if (p == "P")
    {
        Pawn *q = new Pawn(b, curcell, 1);
    }
    else if (p == "p")
    {
        Pawn *q = new Pawn(b, curcell, 2);
    } else if (p == "null") {
        q = nullptr;
    } else {
        throw InvalidMove;
    }

    return q;
}

void Game::setPiece(const string &p, vector<char> pos)
{
    if (mode != 2) {
        cerr << "Invalid command, this command is only valid in set up mode" << endl;
        return;
    }
    try {
        Piece * p = stringtoPiece(board, p, pos);
    } catch (InvalidMove & im) {
        cerr << "Invalid command, " << p << " is not a valid piece." << endl; 
        return;
    }
    board->setPiece(p, pos);
}

void Game::pawnPromote(vector<char> pos, const string & p) {
    piece * upgrade = stringtoPiece(board, p, pos);
    board->setPiece(upgrade, pos_vec);
}

void Game::movePiece(vector<char> start, vector<char> end)
{
    if (winner > 0)
        concludeScore();
    if (mode != 1)
        cerr << "Invalid command, this command is only valid in game mode" << endl;
    
    int curplayer = board->getturn() % 2;
    if (board->getPos(start)->getPiece()->getType() == "pawn") {
        if (end.at(1) == (1 - curplayer) * (BOARDSIZE - 1) {
            // if curplayer is 0, end[1] is 7
            // if curpayer is 1, end[1] is 0
            throw NoPromotion;
        }
    }

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
