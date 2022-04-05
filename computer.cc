#include "computer.h"
#include <cstdlib>
#include <time.h>

using namespace std;


Computer_Lv1::Computer_Lv1(int who, Game *g, int level, float score, King *king): Computer{who, g, level, score, king} {}

Computer_Lv1::~Computer_Lv1() {}

vector<string> randomMove(const vector<vector<char>> possiblestarts, const vector<vector<char>> possibledests) {
    string start;
    string end;
    int size = possibledests.size();
    srand(time(NULL));
    if (size == 0) return vector<string>{"no_moves"};
    int move = rand() % size;

    start.push_back(possiblestarts.at(move)[0]);
    start.push_back(possiblestarts.at(move)[1]);
    end.push_back(possibledests.at(move)[0]);
    end.push_back(possibledests.at(move)[1]);
    return vector<string>{start, end};
}

vector<string> pureRandom(Game *game) {
    int who = (game->getBoard()->getTurn()) % 2;
    vector<vector<char>> possiblestarts;
    vector<vector<char>> possibledests;

    for (auto piece : game->getBoard()->getPieces()) {
        if (piece->getPlayer() != who + 1) continue;
        vector<char> curpos = piece->getPos();
        for (vector<char> move : piece->possibleMoves()) {
            possiblestarts.emplace_back(curpos);
            possibledests.emplace_back(move);
        }
    }

    return randomMove(possiblestarts, possibledests);
}

vector<string> Computer_Lv1::smartMove() {
    return pureRandom(getGame());
}

Computer_Lv2::Computer_Lv2(int who, Game *g, int level, float score, King *king): Computer{who, g, level, score, king} {}
Computer_Lv2::~Computer_Lv2() {}

vector<string> Computer_Lv2::smartMove() {
    vector<vector<char>> cap_and_check_starts;
    vector<vector<char>> cap_and_check_dests;

    vector<vector<char>> cap_or_check_starts;
    vector<vector<char>> cap_or_check_dests;

    int who = (game->getBoard()->getTurn()) % 2;
    for (auto piece : game->getBoard()->getPieces()) {
        if (piece->getPlayer() != who + 1) continue;
        vector<char> curpos = piece->getPos();
        for (vector<char> move : piece->possibleMoves()) {
            Board *b = game->getBoard();
            bool capture{false};
            bool check{false};
            Piece * destp = b->getCell(move)->getPiece();

            if (destp != nullptr)  // has pieces
                capture = true;

            b->getCell(move)->setPiece(piece);
            
            if (game->getPlayers()[2 - who]->getKing()->isChecked()) {
                check = true;
            }

            b->getCell(move)->setPiece(destp);

            if (capture && check) {
                cap_and_check_starts.emplace_back(curpos);
                cap_and_check_dests.emplace_back(move);
            } else if (capture || check) {
                cap_or_check_starts.emplace_back(curpos);
                cap_or_check_dests.emplace_back(move);
            }
        }
    }

    int and_size = cap_and_check_starts.size(); // and is better
    int or_size = cap_or_check_starts.size();
    if (and_size > 0) {
        return randomMove(cap_and_check_starts, cap_and_check_dests);
    } else if (or_size > 0) {
        return randomMove(cap_or_check_starts, cap_or_check_dests);
    } else {
        return pureRandom(game);
    }
}

Computer_Lv3::Computer_Lv3(int who, Game *g, int level, float score, King *king): Computer{who, g, level, score, king} {}

Computer_Lv3::~Computer_Lv3() {}

vector<string> Computer_Lv3::smartMove() {}

Computer_Lv4::Computer_Lv4(int who, Game *g, int level, float score, King *king): Computer{who, g, level, score, king} {}

Computer_Lv4::~Computer_Lv4() {}

vector<string> Computer_Lv4::smartMove() {}



