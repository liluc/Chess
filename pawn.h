#ifndef _PAWN_H_
#define _PAWN_H_
#include <vector>
#include "piece.h"

class Cell;
class Pawn : public Piece{
    int steps;
    // bool enPable;
    //if component step into enPableCells in the next step, current piece will be captured.
    Cell * enPableCell;
    public:
    Pawn(Board *, Cell *, int);

    void setEnPable(bool) override;
    // bool getEnPable() override;
    Cell * getEnPableCell() const;

    bool addCell_PawnMove (int colInc, int rowInc, std::vector<std::vector<char>> &cells);
    void addCell_PawnCapture (int colInc, int rowInc, std::vector<std::vector<char>> &cells);
    std::vector<std::vector<char>> possibleMoves() override;

    //if the cell is enpablecell, then return the piece that make this cell enpable, otherwise, returns nullptr. 
    Piece *isEnPableCell(Cell *) const;
    void move(std::vector<char> pos) override;
    // void promote(Piece *);
    ~Pawn();
};

#endif
