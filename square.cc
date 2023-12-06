#include "square.h"

// Constructor which takes in x, y, and pointer to a Piece
Square::Square(int x, int y, Piece *currPiece): 
    col{x}, row{y}, currPiece{currPiece} {}

Square::~Square() {}


int Square::getX() {
    return col;
}


int Square::getY() {
    return row;
}


Piece* Square::getPiece() {
    return currPiece;
}


void Square::removePiece() {
    currPiece = nullptr;
    notifyDisplayObservers();
}

void Square::removePieceWithoutObservers() {
    currPiece = nullptr;
}

void Square::addPieceWithoutObservers(Piece *piece) {
    currPiece = move(piece);
}


void Square::addPiece(Piece *piece) {
    currPiece = move(piece);
    notifyDisplayObservers(); 
}


bool Square::canPromote() {
    if (col == 0 || col == 7) {
        return true;
    } else {
        return false;
    }
}


void Square::addPieceObservers(Observer *o) {
    possiblePieces.emplace_back(o);
}


void Square::addDisplayObservers(Observer* o) {
    displays.emplace_back(o);
}


void Square::notifyPieceObservers() {
    for (auto p: possiblePieces) {
        p->notify(this);
    }
}


void Square::notifyDisplayObservers() {
    for (auto p: displays) {
         p->notify(this);
    }
}



void Square::removePieceObserver(Observer *o) {
    for (unsigned int i = 0; i < possiblePieces.size(); ++i) { 
        if (possiblePieces[i] == o) {
            possiblePieces.erase(possiblePieces.begin() + i);
        }
    }
}

void Square::removeDisplayObservers(Observer *o) {
    for (unsigned int i = 0; i < possiblePieces.size(); ++i) { 
        if (displays[i] == o) {
            displays.erase(possiblePieces.begin() + i);
        }
    }
}

void Square::turnOffEnPassant() {
    enPassant = false;
}

void Square::turnOnEnPassant() {
    enPassant = true;
}

Square* Square::setX(int x) {
    this->col = x;
    return this;
}

Square* Square::setY(int y) {
    this->row = y;
    return this;
}

bool Square::canEnPassant() {
    return enPassant;
}
