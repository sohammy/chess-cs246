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

    // Returns x value from 0 - 7
    int getX();

    // Returns y value from 0 - 7
    int getY();

    // sets the x value
    Square* setX(int col);

    // sets the y value
    Square* setY(int row);

    // Returns the Piece on the Square
    Piece* getPiece();

    // Removes the Piece from the square (DOES NOT MANAGE MEMORY)
    void removePiece();

    // Making changes ot the Square without telling displays
    void removePieceWithoutObservers();
    void addPieceWithoutObservers(Piece *piece);

    // Adds piece to the Square 
    void addPiece(Piece *piece);

    // If the square is the first or last row, then it has the ability to promote a piece on it
    // so we assign it a bool value to represent this
    bool canPromote();

    // Adds any observers to the vector of observers (namely TextDisplay & GraphicsDisplay)
    void addDisplayObservers(Observer* o);

    // Removes any observers from the vector of observers 
    void removeDisplayObservers (Observer* o);

    // Adds any observers to the vector of observers 
    void addPieceObservers(Observer *o);

    // Removes a Piece Observer
    // should be called whenever a square no longer being observed 
    void removePieceObserver(Observer *o);

    // Notifies piece observers, should be called whenever the contents of the square changes!
    void notifyPieceObservers();

    // Notifies observers (TextDisplay & GraphicsDisplay)
    // should be called whenever the contents of the square changes!
    void notifyDisplayObservers();

    // sets a Square to off if it cannot enPassant
    void turnOffEnPassant();

    // sets a Square to on if it can enPassant
    void turnOnEnPassant();

    // returns whether the Square can enPassant
    bool canEnPassant();
};

#endif
