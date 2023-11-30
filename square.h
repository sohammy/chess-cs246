#ifndef SQUARE_H
#define SQUARE_H
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
    vector<observers*> displays;

    // x & y coordinates of the square
    int x;
    int y;

    // the current piece sitting on the square
    Piece *curpiece;

public:
    Square(int x = 0, int y = 0, Piece *curpiece = nullptr);
    ~Square();
    int getX();
    int getY();
    Piece getPiece();
    void removePiece();
    void addPiece(Piece *piece);
    bool canPromote();
    void addObservers(observer *o);
    void notifyObservers() const;

};

#endif
