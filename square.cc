#include "square.h"

// Constructor which takes in x, y, and pointer to a Piece
Square::Square(int x, int y, Piece *curpiece): 
    x{x}, y{y}, curpiece{curpiece} {}

Square::~Square()

// returns x value from 0 - 7
int Square::getX() {
    return x;
}

// returns y value from 0 - 7
int Square::getY() {
    return y;
}

// returns the Piece on the Square
Piece Square::getPiece() {
    return curpiece;
}

// removes the Piece from the square (DOES NOT MANAGE MEMORY)
void Square::removePiece() {
    curpiece = nullptr;
}

// adds piece to the Square 
void Square::addPiece(Piece *piece) {
    curpiece = piece;
}

// if the square is the first or last row, then it has the ability to promote a piece on it
// so we assign it a bool value to represent this
bool Square::canPromote() {
    if (x == 0 || x == 7) {
        return true;
    } else {
        return false;
    }
}

// Adds any observers to the vector of observers (namely TextDisplay & GraphicsDisplay)
void Square::addObservers(observer *o) {
    displays.emplace_back(o);
}

// notifies observers (TextDisplay & GraphicsDisplay)
// should be called whenever the contents of the square changes!
void Square::notifyObservers() const {
    for (auto p: displays) {
        p->notify(*this);
    }
}
