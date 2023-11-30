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
    vector<Observer*> possiblePieces;

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
    Piece* getPiece();
    void removePiece();
    void addPiece(Piece *piece);
    bool canPromote();
    void addDisplayObservers(Observer *o);
    void addPieceObservers(Observer *o);
    void notifyPieceObservers();
    void notifyDisplayObservers();

};

#endif
