#ifndef __piece_H__
#define __piece_H__
#include <memory>
#include <vector>
#include <iostream>
#include <string>
#include "moves.h"
using namespace std;

enum Color {white, black};

class Piece {

private:
    Color piece_color;


public:
    virtual bool canMove(Square) = 0;
    virtual vector<Moves> getMoves() = 0;

    void setColour(char);
}


#endif
