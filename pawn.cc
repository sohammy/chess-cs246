#include "pawn.h"

Pawn::Pawn(vector<vector<Square>>& board, char pieceType): Piece(board, pieceType) {}

void Pawn::calculateMoves() {
    int x = position->getX();
    int y = position->getY();

    possibleMoves.clear();
    blockedMoves.clear();

    bool doubleStep = canDoubleStep();


    if(doubleStep) {
        if (pieceColour == WHITE) {
            Move s1 = Move(x, y, x - 1, y, &theBoard[x - 1][y], N);
            Move s2 = Move(x, y, x - 2, y, &theBoard[x - 2][y], N);
            possibleMoves.emplace_back(s1);
            possibleMoves.emplace_back(s2);
            theBoard[x - 1][y].addPieceObservers(this);
            theBoard[x - 2][y].addPieceObservers(this);
        } else if (pieceColour == BLACK) {
            Move s1 = Move(x, y, x + 1, y, &theBoard[x + 1][y], S);
            Move s2 = Move(x, y, x + 2, y, &theBoard[x + 2][y], S);
            possibleMoves.emplace_back(s1);
            possibleMoves.emplace_back(s2);
            theBoard[x + 1][y].addPieceObservers(this);
            theBoard[x + 2][y].addPieceObservers(this);
        }
    } else {
        if (pieceColour == WHITE) {
            if (x > 0) {
                if(theBoard[x - 1][y].getPiece() == nullptr) {
                    Move s1 = Move(x, y, x - 1, y, &theBoard[x - 1][y], N);
                    possibleMoves.emplace_back(s1);
                    theBoard[x - 1][y].addPieceObservers(this);
                }
            }
        } else if (pieceColour == BLACK) {
            if (x < 7) {
                if(theBoard[x + 1][y].getPiece() == nullptr) {
                    Move s1 = Move(x, y, x + 1, y, &theBoard[x + 1][y], S);
                    possibleMoves.emplace_back(s1);
                    theBoard[x + 1][y].addPieceObservers(this);
                }
            }
        }
    }

    if(pieceColour == WHITE) {
        if (x > 0) {
            if (y < 7) {
                if (theBoard[x - 1][y + 1].getPiece() != nullptr && theBoard[x - 1][y + 1].getPiece()->getColour() != pieceColour) {
                    Move s1 = Move(x, y, x - 1, y + 1, &theBoard[x - 1][y + 1], NE);
                    possibleMoves.emplace_back(s1);
                    theBoard[x - 1][y + 1].addPieceObservers(this);
                } else if (theBoard[x - 1][y + 1].canEnPassant()) {
                    Move s1 = Move(x, y, x - 1, y + 1, &theBoard[x - 1][y + 1], NE);
                    possibleMoves.emplace_back(s1);
                    theBoard[x - 1][y + 1].addPieceObservers(this);
                }
                else {
                    Move s1 = Move(x, y, x - 1, y + 1, &theBoard[x - 1][y + 1], NE);
                    blockedMoves.emplace_back(s1);
                }
            } 
            if (y > 0) {
                if (theBoard[x - 1][y - 1].getPiece() != nullptr && theBoard[x - 1][y - 1].getPiece()->getColour() != pieceColour) {
                    Move s1 = Move(x, y, x - 1, y - 1, &theBoard[x - 1][y - 1], NW);
                    possibleMoves.emplace_back(s1);
                    theBoard[x - 1][y - 1].addPieceObservers(this);
                } else if (theBoard[x - 1][y - 1].canEnPassant()) {
                    Move s1 = Move(x, y, x - 1, y - 1, &theBoard[x - 1][y - 1], NW);
                    possibleMoves.emplace_back(s1);
                    theBoard[x - 1][y - 1].addPieceObservers(this);
                }
                else {
                    Move s1 = Move(x, y, x - 1, y - 1, &theBoard[x - 1][y - 1], NW);
                    blockedMoves.emplace_back(s1); 
                }
            }
        } 
    }
    if(pieceColour == BLACK) {
        if (x < 7) {
            if (y < 7) {
                if (theBoard[x + 1][y + 1].getPiece() != nullptr && theBoard[x + 1][y + 1].getPiece()->getColour() != pieceColour) {
                    Move s1 = Move(x, y, x + 1, y + 1, &theBoard[x + 1][y + 1], SE);
                    possibleMoves.emplace_back(s1);
                    theBoard[x + 1][y + 1].addPieceObservers(this);
                } else if (theBoard[x + 1][y + 1].canEnPassant()) {
                    Move s1 = Move(x, y, x + 1, y + 1, &theBoard[x + 1][y + 1], SE);
                    possibleMoves.emplace_back(s1);
                    theBoard[x + 1][y + 1].addPieceObservers(this);
                } else {
                    Move s1 = Move(x, y, x + 1, y + 1, &theBoard[x + 1][y + 1], SE);
                    blockedMoves.emplace_back(s1);
                }
            } 
            if (y > 0) {
                if (theBoard[x + 1][y - 1].getPiece() != nullptr && theBoard[x + 1][y - 1].getPiece()->getColour() != pieceColour) {
                    Move s1 = Move(x, y, x + 1, y - 1, &theBoard[x + 1][y - 1], SW);
                    possibleMoves.emplace_back(s1);
                    theBoard[x + 1][y - 1].addPieceObservers(this);
                } else if (theBoard[x + 1][y - 1].canEnPassant()) {
                    Move s1 = Move(x, y, x + 1, y - 1, &theBoard[x + 1][y - 1], SW);
                    possibleMoves.emplace_back(s1);
                    theBoard[x + 1][y - 1].addPieceObservers(this);
                } else {
                    Move s1 = Move(x, y, x + 1, y - 1, &theBoard[x + 1][y - 1], SW);
                    blockedMoves.emplace_back(s1);
                }
            }
        } 
    }
}

bool Pawn::canDoubleStep() {
    int x = position->getX();
    int y = position->getY();
    if(!hasMoved) { 
        if(pieceColour == WHITE && x == 6) {
            if(theBoard[x - 1][y].getPiece() == nullptr) {
                if(theBoard[x - 2][y].getPiece() == nullptr) {
                    return true;
                }
            }
        } else if ( pieceColour == BLACK && x == 1) {
            if(theBoard[x + 1][y].getPiece() == nullptr) {
                if(theBoard[x + 2][y].getPiece() == nullptr) {
                    return true;
                }
            }
        }
    }
    return false;
}
