#ifndef SQUARE_H
#define SQUARE_H
#include "observer.h"
// #include "piece.h"
#include <memory>
#include <vector>
#include <iostream>
#include <string>
using namespace std;

class Piece;

class Square {

private:
    // Vector of observers (TextDisplay & GraphicsDisplay)
    vector<Observer*> displays;
    vector<Observer*> possiblePieces;

    // x & y coordinates of the square
    int col;
    int row;

    // The current piece sitting on the square
    Piece* currPiece;

    bool enPassant;

public:
    Square(int x = 0, int y = 0, Piece *currPiece = nullptr);
    ~Square();
    int getX();
    int getY();
    Square* setX(int col);
    Square* setY(int row);
    Piece* getPiece();
    void removePiece();
    void addPiece(Piece *piece);
    bool canPromote();
    void addDisplayObservers(Observer* o);
    void addPieceObservers(Observer *o);
    void removePieceObserver(Observer *o);
    void notifyPieceObservers();
    void notifyDisplayObservers();
    void turnOffEnPassant();
    void turnOnEnPassant();
    bool canEnPassant();
};

#endif
