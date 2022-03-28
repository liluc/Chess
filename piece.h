#ifndef _PIECE_H_
#define _PIECE_H_
#include <vector>

class Cell;
class Piece
{
    Cell *cell;
    int player;
    /* suggestions
    string type;    note: type for Knight is "night" for convenience
    */

public:
    Piece(Cell *, int);
    virtual std::vector<std::vector<char>> possibleMoves() = 0;
    virtual void move(std::vector<char>) = 0;
    virtual ~Piece();
    /* suggestions
    string getType() const;
    */
};

#endif
