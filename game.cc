#include "game.h"
#include "player.h"
#include "piece.h"
#include "player.h"
#include "exception.h"
#include <iostream>
using namespace std;


Game::Game()
{
    Board * newboard = new Board();
    board = newboard;
    vector<Player *> np;
    players = np;
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
    board->setState(true);
}

void Game::setMode(int m) {
    mode = m;
}

void Game::addPlayers(Player * p) {
    players.emplace_back(p);
}

// board builder methods
void Game::fillinPieces()
{
    const int BOARDSIZE = 8;
    vector<vector<Cell *>> grid = board->getBoard();
    for (int i = 0; i < BOARDSIZE; ++i)
    {
        Pawn *pawn1 = new Pawn{board, grid.at(i).at(1), 1};
        Pawn *pawn2 = new Pawn{board, grid.at(i).at(6), 2};
        board->pushPieces(pawn1);
        board->pushPieces(pawn2);
        grid.at(i).at(1)->setPiece(pawn1);
        grid.at(i).at(6)->setPiece(pawn2);

        //added by Lucas
        Piece *p1, *p2;
        if (i == 0 || i == 7)
        {
            p1 = new Rook{board, grid.at(i).at(0), 1};
            p2 = new Rook{board, grid.at(i).at(7), 2};
        }
        else if (i == 1 || i == 6)
        {
            p1 = new Knight{board, grid.at(i).at(0), 1};
            p2 = new Knight{board, grid.at(i).at(7), 2};
        }
        else if (i == 2 || i == 5)
        {
            p1 = new Bishop{board, grid.at(i).at(0), 1};
            p2 = new Bishop{board, grid.at(i).at(7), 2};
        }
        else if (i == 3)
        {
            p1 = new Queen{board, grid.at(i).at(0), 1};
            p2 = new Queen{board, grid.at(i).at(7), 2};
        }
        else
        {
            King *p3 = new King{board, grid.at(i).at(0), 1};
            King *p4 = new King{board, grid.at(i).at(7), 2};
            players[0]->setKing(p3);
            players[1]->setKing(p4);
            p1 = p3;
            p2 = p4;
        }
        board->pushPieces(p1);
        board->pushPieces(p2);
        grid.at(i).at(0)->setPiece(p1);
        grid.at(i).at(7)->setPiece(p2);
    }
}

/*
void Game::runGame(string white, string black)
{
    mode = 1;
    winner = 0;
    if (white == "computer[1]")
    {
        players[0]->setLevel(1);
    }
    else if (white == "computer[2]")
    {
        players[0]->setLevel(2);
    }
    else if (white == "computer[3]")
    {
        players[0]->setLevel(3);
    }
    else if (white == "computer[4]")
    {
        players[0]->setLevel(4);
    }
    else if (white == "human")
    {
        players[0]->setLevel(0);
    }
    else
    {
        cerr << "Invalid player type for white player!" << endl;
    }
    // for black
    if (black == "computer[1]")
    {
        players[1]->setLevel(1);
    }
    else if (black == "computer[2]")
    {
        players[1]->setLevel(2);
    }
    else if (black == "computer[3]")
    {
        players[1]->setLevel(3);
    }
    else if (black == "computer[4]")
    {
        players[1]->setLevel(4);
    }
    else if (black == "human")
    {
        players[1]->setLevel(0);
    }
    else
    {
        cerr << "Invalid player type for black player!" << endl;
    }

    if (board->getPieces().size() == 0)
        fillinPieces();

    // fillin the pieces
}
*/

void Game::setup()
{
    mode = 2;
    delete board;
    delete hist;

    Board *newboard = new Board();
    board = newboard;
    History *newhist = new History();
    hist = newhist;
}

void Game::exitsetup()
{
    int white_king{0};
    int black_king{0};
    bool no_pawn_promoted{true};

    Piece *kingW, *kingB;
    for (auto piece : board->getPieces())
    {
        if (piece->getType() == "pawn")
        {
            if (piece->getPlayer() == 1)
            {
                no_pawn_promoted = no_pawn_promoted && (piece->getCell()->getPos().at(1) != '8');
            }
            else
            {
                no_pawn_promoted = no_pawn_promoted && (piece->getCell()->getPos().at(1) != '1');
            }
        }
        else if (piece->getType() == "king")
        {
        
            if (piece->getPlayer() == 1)
            {
                white_king += 1;
                kingW = piece;
            }
            else
            {
                black_king += 1;
                kingB = piece;
            }
        }
    }

    bool ret = (white_king == 1) && (black_king == 1);
    if (ret) {
        ret = ret && (!(kingW->isChecked())) && (!(kingB->isChecked())) && no_pawn_promoted;
    } 
    if (!ret)
    {
        cerr << "Invalid board set up, cannot exit set up mode." << endl;
    }
    else
    {
        mode = 3;
    }
}

// helper function to turn string input to a corresponding piece and throw exception if 
Piece * stringtoPiece(Board * b, const string &p, vector<char> pos) {
    Cell *curcell = b->getBoard().at(pos[0] - 'a').at(pos[1] - '1');
    Piece *q;
    if (p == "K")
    {
        q = new King(b, curcell, 1);
    }
    else if (p == "k")
    {
        q = new King(b, curcell, 2);
    }
    else if (p == "Q")
    {
        q = new Queen(b, curcell, 1);
    }
    else if (p == "q")
    {
        q = new Queen(b, curcell, 2);
    }
    else if (p == "R")
    {
        q = new Rook(b, curcell, 1);
    }
    else if (p == "r")
    {
        q = new Rook(b, curcell, 2);
    }
    else if (p == "N")
    {
        q = new Knight(b, curcell, 1);
    }
    else if (p == "n")
    {
        q = new Knight(b, curcell, 2);
    }
    else if (p == "B")
    {
        q = new Bishop(b, curcell, 1);
    }
    else if (p == "b")
    {
        q = new Bishop(b, curcell, 2);
    }
    else if (p == "P")
    {
        q = new Pawn(b, curcell, 1);
    }
    else if (p == "p")
    {
        q = new Pawn(b, curcell, 2);
    } else if (p == "null") {
        q = nullptr;
    } else {
        InvalidMove invalid;
        throw invalid;
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
        Piece * piece = stringtoPiece(board, p, pos);
        board->setPiece(piece, pos);
        if (p == "K" ) {
            players[0]->setKing(static_cast<King *>(piece));
        } else if (p == "k") {
            players[1]->setKing(static_cast<King *>(piece));
        }
    } catch (InvalidMove & im) {
        cerr << "Invalid command, " << p << " is not a valid piece." << endl; 
        return;
    }
}

void Game::pawnPromote(vector<char> pos, const string & p) {
    Piece * upgrade = stringtoPiece(board, p, pos);
    vector<char> pos_vec;
    pos_vec.emplace_back(pos[0]);
    pos_vec.emplace_back(pos[1]);
    board->setPiece(upgrade, pos_vec);
}

void Game::movePiece(vector<char> start, vector<char> end)
{
    //testing cout
    // cout << "game: movePiece called" << endl;
    
    InvalidMove im;
    const int BOARDSIZE = 8;
    if (winner > 0) {
        cerr << "This game has already ended, please start a new game" << endl; 
        throw im;
    }
    if (mode != 1) {
        cerr << "Invalid command, this command is only valid in game mode" << endl;
        throw im;
    }   
    
    int curplayer = board->getTurn() % 2;
    if (board->checkPos(start)->getType() == "pawn") {
        if (end.at(1) == (1 - curplayer) * (BOARDSIZE - 1)) {
            // if curplayer is 0, end[1] is 7
            // if curpayer is 1, end[1] is 0
            NoPromotion nopromotion;
            throw nopromotion;
        }
    }

    try
    {
        board->movePiece(start, end);
        //there is no board->movePiece ??
    }
    catch (InvalidMove &im)
    {
        cerr << "This move is invalid, please check chess rulesheet or seek mental support" << endl;
    }
    if (isCheckmate())
    {
        if (players.at(0)->getKing()->isChecked())
        {
            winner = 2;
        }
        else {
            winner = 1;
        }
    } 
    else if (isStalemate()) {
        winner = 3;
    }
    if (winner > 0) {
        concludeScore();
    }
}

void Game::concludeScore() const
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

bool Game::isStalemate() const
{
    // return false;
    //testing cout
    // cout << "isStalemate is called" << endl;

    bool checked = (players[0]->getKing()->isChecked() || players[1]->getKing()->isChecked());
    if (checked) return false;

    //testing cout
    // cout << "checked is false" << endl;
    // cout << board->getPieces().back() << endl; //returns segfault, board->pieces vector is not initialized!

    bool stale{!(checked)}; //original stale is true

    for (auto piece : board->getPieces()) {

        if (((board->getTurn() % 2) + 1) != piece->getPlayer()){
            
            continue;
        }

        int pos_moves = piece->possibleMoves().size();
        

        stale = stale && (pos_moves == 0);
    }
    return stale;
}


//isCheckmate in move piece goes first
//isCheckmate in display goes second
bool Game::isCheckmate() const {

    //testing cout
    // cout << "isCheckmate is called" << endl;

    bool checked = (players[0]->getKing()->isChecked() || players[1]->getKing()->isChecked());
    
    
    if (!(checked)) return false;

    int checkedPlayer = players[0]->getKing()->isChecked() ? 1 : 2;
    //testing cout
    // cout << "possible moves" << endl;
    // for (auto piece : board->getPieces()){
    //     cout << piece->getPos()[0] << piece->getPos()[1] << ": ";
    //     cout << piece->possibleMoves().size() << endl;
    // }
    //


    for (auto piece : board->getPieces()) {
        // ((board->getTurn() % 2) + 1) 
        if (checkedPlayer != piece->getPlayer())
            continue;
        vector<vector<char>> possible = piece->possibleMoves();
        int pos_moves = possible.size();

        //testing cout
        if (pos_moves != 0){
            cout << "possible moves for " << piece->getPos()[0] << piece->getPos()[1] << endl;
            for (auto pos : possible){
                cout << pos[0] << pos[1] << endl;
                if (board->checkPos(pos)){
                    cout << "this is a " << board->checkPos(pos)->getType() << endl;
                } else {
                    cout << "this is an empty cell" << endl;
                }
            }
        }

        checked = checked && (pos_moves == 0);
    }
    return checked;
}
