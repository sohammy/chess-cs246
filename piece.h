#ifndef __piece_H__
#define __piece_H__
#include <memory>
#include <vector>
#include <iostream>
#include <string>
#include "moves.h"
using namespace std;

class Piece {
    enum Colour {white, black};

private:
    Colour pieceColour;
    int xCoord;
    int yCoord;

public:
    virtual vector<Move> getMoves() = 0;
    void setColour(char c);
    int getX() { return xCoord; }
    int getY() { return yCoord; }
    Colour getColour() { return pieceColour; }

};


#endif
 