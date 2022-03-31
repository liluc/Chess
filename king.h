#ifndef _KING_H_
#define _KING_H_
#include <vector>
#include "piece.h"

class Cell;
class King : public Piece
{
public:
    King(Board *, Cell *, int);
    std::vector<std::vector<char>> possibleMoves() override;
    ~King();
    bool isChecked() override;

    /* suggestions
    bool ischecked() const;
    bool ischeckmate() const;
    */
};

#endif
