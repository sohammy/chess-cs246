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
    // Vector of observers (TextDisplay & GraphicsDisplay)
    vector<Observer*> displays;

    // x & y coordinates of the square
    int x;
    int y;

    // The current piece sitting on the square
    Piece *currPiece;

public:
    Square(int x = 0, int y = 0, Piece *currPiece = nullptr);
    ~Square();
    int getX();
    int getY();
    Piece getPiece();
    void removePiece();
    void addPiece(Piece *piece);
    bool canPromote();
    void addObservers(Observer *o);
    void notifyObservers() const;

};

#endif
