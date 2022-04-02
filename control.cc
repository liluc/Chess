#include "control.h"

Control::Control(Game *game): g{game}, td{new TextDisplay{game}}, gd{new GraphicDisplay{game}} {}

Control::~Control() {
    delete td;
    delete gd;
}

void * Control::createPlayer(int who, const string & identity) {
    if (identity == "human") {
        p = new Human{who};
    } else if (identity == "computer[1]") {
        p = new Computer_Lv1{who, 1};
    } else if (identity == "computer[2]") {
        p = new Computer_Lv2{who, 2};
    } else if (identity == "computer[3]") {
        p = new Computer_Lv3{who, 3};
    } else if (identity == "computer[4]") {
        p = new Computer_Lv4{who, 4};
    } else {
        cerr << "Invalid Player types" << endl;
    }
}

void Control::makeMove(int turn) {
    int who = (turn % 2) + 1;

    string smartmove = game->getPlayers[who].smartMove();
    if (smartmove == "no_suggestions") {
        string cmd;
        cin >> cmd;
        if (cmd == "resign") {
            game->setWinner(1 - who);
        } else if (cmd == "move") {
            string start;
            string end;
            cin >> start >> end; 
            if (start.length() < 2 || end.length() < 2) {
                cerr << "Invalid input" << endl;
                continue;
            } 
            if (!(start[0] < 'a' || start[0] > 'h')){
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
        char start_1 = smartmove.at(0)[0];
        char start_2 = smartmove.at(0)[1];
        char end_1 = smartmove.at(1)[0];
        char end_2 = smartmove.at(1)[1];
        
        game->movePiece(vector<char>{start_1, start_2}, vector<char>{end_1, end_2});
    }
    display();
}

void Control::runGame() {
    string cmd;
    int turn = 0;
    game->setWinner(0);
    while (game->getWinner() == 0) {
        makeMove(turn);
        turn += 1;
    }
    displayScore();
}