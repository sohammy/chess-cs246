#ifndef PIECE_H
#define PIECE_H__
#include <memory>
#include <vector>
#include <iostream>
#include <string>
#include "move.h"
using namespace std;

class Piece {
    enum Colour {white, black};

private:
    Colour pieceColour;
    Square* position;

public:
    virtual vector<Move> getMoves() = 0;
    void setColour(char c);
    int getX() { return position->getX(); }
    int getY() { return position->getY(); }
    Colour getColour() { return pieceColour; }

};


#endif
 