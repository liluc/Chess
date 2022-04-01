#ifndef _KING_H_
#define _KING_H_
#include <vector>
#include "piece.h"
#include "observer.h"

class Cell;
class King : public Piece, public Observer {
public:
    King(Board *, Cell *, int);
    std::vector<std::vector<char>> possibleMoves() override;
    ~King();
    bool isChecked() const override;
    bool isCheckMate() const;
    /* suggestions
    bool ischecked() const;
    bool ischeckmate() const;
    */
};

#endif
