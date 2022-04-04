#include "control.h"

#include <string>
using namespace std;

Control::Control(Game *game): game{game}, td{new TextDisplay{game}}, gd{new GraphicDisplay{game}} {}

Control::~Control() {
    delete td;
    delete gd;
}

Game * Control::getGame() const {
    return game;
}

// kinds functions like a copy ctor
void Control::createPlayer(int who, const string & identity) {
    Player *p;
    float sc = 0;
    King *k = nullptr;
    Player *old = nullptr;
    int Player_size = game->getPlayers().size();
    if (Player_size == 2) {
        old = game->getPlayers()[who - 1];
        sc = old->getScore();
        k = old->getKing();
    } 
    if (identity == "human") {
        p = new Human{who, game, sc, k};
    } else if (identity == "computer[1]") {
        p = new Computer_Lv1{who, game, 1, sc, k};
    } else if (identity == "computer[2]") {
        p = new Computer_Lv2{who, game, 2, sc, k};
    } else if (identity == "computer[3]") {
        p = new Computer_Lv3{who, game, 3, sc, k};
    } else if (identity == "computer[4]") {
        p = new Computer_Lv4{who, game, 4, sc, k};
    } else {
        cerr << "Invalid Player types" << endl;
    }
    delete old;

    game->addPlayers(p);

}

void Control::makeMove(int turn) {
    int who = (turn % 2) + 1;

    vector<string> smartmove = game->getPlayers()[who - 1]->smartMove();
    if (smartmove[0] == "no_suggestions") {
        string cmd;
        cin >> cmd;
        if (cmd == "resign") {
            game->setWinner(3 - who);
            game->concludeScore();
            return;
        } else if (cmd == "move") {
            string start;
            string end;
            cin >> start >> end; 
            if (start.length() < 2 || end.length() < 2) {
                cerr << "Invalid input" << endl;
                return;
            } 
            if ((start[0] < 'a') || (start[0] > 'h') || (start[1] < '1') || (start[1] > '8') ||
                (end[0] < 'a') || (end[0] > 'h') || (end[1] < '1') || (end[1] > '8')) {
                return;
            }
            vector<char> vStart{start[0], start[1]};
            vector<char> vEnd{end[0], end[1]};
            try {
                game->movePiece(vStart, vEnd);
            } catch (NoPromotion &) {
                string upgrade;
                cin >> upgrade;
                try {
                    game->pawnPromote(vEnd, upgrade);
                } catch (InvalidMove &) {
                    cerr << "Invalid Move command" << endl;
                }
            } catch (InvalidMove &) {
                cerr << "Invalid Move command" << endl;
            }

        } else {
            cerr << "Invalid command, you can only move a piece or resign!" << endl;
        }
    } else {
        // computermoves
        string start = smartmove.at(0);
        if (start == "no_moves") {
            game->setWinner(3 - who);
            game->concludeScore();
            return;
        }
        string end = smartmove.at(1);
        char start_1 = start[0];
        char start_2 = start[1];
        char end_1 = end[0];
        char end_2 = end[1];
        
        game->movePiece(vector<char>{start_1, start_2}, vector<char>{end_1, end_2});
    }
}

void Control::runGame(string white, string black) {
    string cmd;
    int turn = game->getBoard()->getTurn();
    game->setWinner(0);
    if (game->getPlayers().size() != 2) {
        createPlayer(1, white);
        createPlayer(2, black);
    }
    int last_mode = game->getMode();
    if (last_mode < 2) {
        game->fillinPieces();
    }

    game->setMode(1);
    td->display();
    gd->display();
    while (game->getWinner() == 0 && !(cin.eof()) && turn < 100) {
        makeMove(turn);
        turn += 1;
    }
    game->getPlayers()[0]->setKing(nullptr);
    game->getPlayers()[1]->setKing(nullptr);
    td->displayWinner();
    td->displayScore();
}

void Control::pieceSetup() {
    game->setup();
    game->getBoard()->attach(td);
    game->getBoard()->attach(gd); // reattach the observers to the new board
    if (game->getPlayers().size() != 2) {
        createPlayer(1, "human");
        createPlayer(2, "human");
    }
    td->display();
    gd->display();
    string type;
    cin >> type;
    while (cin && game->getMode() == 2)
    {
        if (type == "+") {
            string piece;
            string pos;
            cin >> piece >> pos;
            if (pos.size() < 2) cerr << "Invalid position" << endl;
            if (pos[0] < 'a' || pos[0] > 'h' || pos[1] < '1' || pos[1] > '8') {
                cerr << "Invalid position" << endl;
            }
            vector<char> vPos{pos[0], pos[1]};
            game->setPiece(piece, vPos);
        }

        else if (type == "-") {
            string pos;
            cin >> pos;
            if (pos.size() < 2) cerr << "Invalid position" << endl;
            if (pos[0] < 'a' || pos[0] > 'h' || pos[1] < '1' || pos[1] > '8') {
                cerr << "Invalid position" << endl;
            }
            vector<char> vPos{pos[0], pos[1]};
            game->setPiece("null", vPos);
        }

        // colour should only be black and white for now.
        else if (type == "=")
        {
            string player;
            cin >> player;
            if (player == "white")
            {
                game->getBoard()->setTurn(0);
            }
            else if (player == "black")
            {
                game->getBoard()->setTurn(1);
            }
            cout << "current player set to " << player << endl;
        } else if (type == "done") {
            game->exitsetup();
        } else {
            cerr << "Invalid command for setup" << endl;
        }
        if (game->getMode() == 2) {
            cin >> type;
        }
    }
}

