#include "pawn.h"

Pawn::Pawn(vector<vector<Square>>& board, char pieceType): Piece(board, pieceType) {}

void Pawn::calculateMoves() {
    //cout << "In Pawn" << endl;
    int x = position->getX();
    int y = position->getY();
    //cout << "1" << endl;

    possibleMoves.clear();
    blockedMoves.clear();
    //cout << "2" << endl;

    bool doubleStep = canDoubleStep();
    //cout << "3" << endl;


    if(doubleStep) {
        if(pieceColour == WHITE) {
            movesInDir(N,2);
        } else if (pieceColour == BLACK) {
            movesInDir(S,2);
        }
    } else {
        if(pieceColour == WHITE) {
            if (x > 0) {
                movesInDir(N,1);
            }
        } else if(pieceColour == BLACK) {
            if (x < 7) {
                movesInDir(S,1);
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
                }
            } 
            if (y > 0) {
                if (theBoard[x - 1][y - 1].getPiece() != nullptr && theBoard[x - 1][y - 1].getPiece()->getColour() != pieceColour) {
                    Move s1 = Move(x, y, x - 1, y - 1, &theBoard[x - 1][y - 1], NW);
                    possibleMoves.emplace_back(s1);
                    theBoard[x - 1][y - 1].addPieceObservers(this);
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
