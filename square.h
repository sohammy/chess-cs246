#ifndef __SQUARE_H__
#define __SQUARE_H__
#include "observer.h"
#include "piece.h"
#include <memory>
#include <vector>
#include <iostream>
#include <string>
using namespace std;

class Square {

private:
    // vector of observers (TextDisplay & GraphicsDisplay)
    vector<observers*>;

    // x & y coordinates of the square
    int x;
    int y;

    // the current piece sitting on the square
    Piece *curpiece;

public:
    int getX();
    int getY();
    Piece getPiece();
    bool canPromote();
    void addObservers();
    void notifyObservers();
};


#endif
