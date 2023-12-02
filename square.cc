#include "square.h"

// Constructor which takes in x, y, and pointer to a Piece
Square::Square(int x, int y, Piece *currPiece): 
    x{x}, y{y}, currPiece{currPiece} {}

Square::~Square() {}

// Returns x value from 0 - 7
int Square::getX() {
    return x;
}

// Returns y value from 0 - 7
int Square::getY() {
    return y;
}

// Returns the Piece on the Square
Piece* Square::getPiece() {
    return currPiece;
}

// Removes the Piece from the square (DOES NOT MANAGE MEMORY)
void Square::removePiece() {
    currPiece = nullptr;
    notifyDisplayObservers();
}

// Adds piece to the Square 
void Square::addPiece(Piece *piece) {
    currPiece = move(piece);
    
    notifyDisplayObservers();
}

// If the square is the first or last row, then it has the ability to promote a piece on it
// so we assign it a bool value to represent this
bool Square::canPromote() {
    if (x == 0 || x == 7) {
        return true;
    } else {
        return false;
    }
}

// Adds any observers to the vector of observers 
void Square::addPieceObservers(Observer *o) {
    possiblePieces.emplace_back(o);
}

// Adds any observers to the vector of observers (namely TextDisplay & GraphicsDisplay)
void Square::addDisplayObservers(Observer* o) {
    displays.emplace_back(o);
}

// Notifies piece observers, should be called whenever the contents of the square changes!
void Square::notifyPieceObservers() {
    for (auto p: possiblePieces) {
        p->notify(this);
    }
}

// Notifies observers (TextDisplay & GraphicsDisplay)
// should be called whenever the contents of the square changes!
void Square::notifyDisplayObservers() {
    for (auto p: displays) {
         p->notify(this);
    }
}

// Removes a Piece Observer
// should be called whenever a square no longer being observed 

void Square::removePieceObserver(Observer *o) {
    for (unsigned int i = 0; i < possiblePieces.size(); ++i) { 
        if (possiblePieces[i] == o) {
            possiblePieces.erase(possiblePieces.begin() + i);
        }
    }
}

Square* Square::setX(int x) {
    this->x = x;
    return this;
}

Square* Square::setY(int y) {
    this->y = y;
    return this;
}

bool Square::canEnPassant() {
    return enPassant;
}