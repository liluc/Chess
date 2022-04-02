#include "history.h"
#include <vector>
#include <iostream>
using namespace std;

History::History():histBoard{new vector<Board *>}{
}

void History::push(Board *board){
    histBoard->emplace_back(board);
}

Board * History::pop(){
    Board *last = histBoard->back();
    histBoard->pop_back();
    return last;
}

Board * History::top(){
    return histBoard->back();
}

History::~History(){
    for (auto board : *histBoard){
        delete board;
    }
    delete histBoard;
}
