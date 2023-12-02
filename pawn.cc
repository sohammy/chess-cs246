#include "pawn.h"

Pawn::Pawn(vector<vector<Square>>& board, char pieceType): Piece(board, pieceType) {}

void Pawn::calculateMoves() {
    cout << "in pawn" << endl;
    possibleMoves.clear();
    blockedMoves.clear();

    bool doubleStep = canDoubleStep();

    if(doubleStep) {
        if(pieceColour == WHITE) {
            Move s1 = Move(position->getX(), position->getY(), position->getX(), 
            position->getY() - 1, N, &theBoard[position->getX()][position->getY() - 1]);
            Move s2 = Move(position->getX(), position->getY(), position->getX(), 
            position->getY() - 2, N, &theBoard[position->getX()][position->getY() - 2]);
            possibleMoves.emplace_back(s1);
            possibleMoves.emplace_back(s2);
        } else if (pieceColour == BLACK) {
            Move s1 = Move(position->getX(), position->getY(), position->getX(), 
            position->getY() + 1, S, &theBoard[position->getX()][position->getY() + 1]);
            Move s2 = Move(position->getX(), position->getY(), position->getX(), 
            position->getY() + 2, S, &theBoard[position->getX()][position->getY() + 2]);
            possibleMoves.emplace_back(s1);
            possibleMoves.emplace_back(s2);
        }
    } else {
        if(pieceColour == WHITE) {
            if (position->getY() > 0) {
                if(theBoard[position->getX()][position->getY() - 1].getPiece() == nullptr) {
                    Move s1 = Move(position->getX(), position->getY(), position->getX(), 
                    position->getY() - 1, N, &theBoard[position->getX()][position->getY() - 1]);
                    possibleMoves.emplace_back(s1);
                }
            }
        } else if(pieceColour == BLACK) {
            if (position->getY() < 7) {
                if(theBoard[position->getX()][position->getY() + 1].getPiece() == nullptr) {
                    Move s1 = Move(position->getX(), position->getY(), position->getX(), 
                    position->getY() + 1, S, &theBoard[position->getX()][position->getY() + 1]);
                    possibleMoves.emplace_back(s1);
                }
            }
        }
    }

    if(pieceColour == WHITE) {
        if (position->getY() > 0) {
            if (position->getX() < 7) {
                if (theBoard[position->getX() + 1][position->getY() - 1].getPiece() != nullptr && 
                theBoard[position->getX() + 1][position->getY() - 1].getPiece()->getColour() != pieceColour) {
                    Move s1 = Move(position->getX(), position->getY(), position->getX() + 1, 
                    position->getY() - 1, N, &theBoard[position->getX() + 1][position->getY() - 1]);
                    possibleMoves.emplace_back(s1);
                }
            } else if (position->getX() > 0) {
                if (theBoard[position->getX() - 1][position->getY() - 1].getPiece() != nullptr && 
                theBoard[position->getX() - 1][position->getY() - 1].getPiece()->getColour() != pieceColour) {
                    Move s1 = Move(position->getX(), position->getY(), position->getX() - 1, 
                    position->getY() - 1, N, &theBoard[position->getX() - 1][position->getY() - 1]);
                    possibleMoves.emplace_back(s1);
                }
            }
        } 
    }
    if(pieceColour == BLACK) {
        if (position->getY() < 7) {
            if (position->getX() < 7) {
                if (theBoard[position->getX() + 1][position->getY() + 1].getPiece() != nullptr && 
                theBoard[position->getX() + 1][position->getY() + 1].getPiece()->getColour() != pieceColour) {
                    Move s1 = Move(position->getX(), position->getY(), position->getX() + 1, 
                    position->getY() + 1, S, &theBoard[position->getX() + 1][position->getY() + 1]);
                    possibleMoves.emplace_back(s1);
                } else if (theBoard[position->getX() + 1][position->getY() + 1].canEnPassant()) {
                    Move s1 = Move(position->getX(), position->getY(), position->getX() + 1, 
                    position->getY() + 1, S, &theBoard[position->getX() + 1][position->getY() + 1]);
                    possibleMoves.emplace_back(s1);
                }
            } else if (position->getX() > 0) {
                if (theBoard[position->getX() - 1][position->getY() + 1].getPiece() != nullptr && 
                theBoard[position->getX() - 1][position->getY() + 1].getPiece()->getColour() != pieceColour) {
                    Move s1 = Move(position->getX(), position->getY(), position->getX() - 1, 
                    position->getY() + 1, S, &theBoard[position->getX() - 1][position->getY() + 1]);
                    possibleMoves.emplace_back(s1);
                } else if(theBoard[position->getX() - 1][position->getY() + 1].canEnPassant()) {
                    Move s1 = Move(position->getX(), position->getY(), position->getX() - 1, 
                    position->getY() + 1, S, &theBoard[position->getX() - 1][position->getY() + 1]);
                    possibleMoves.emplace_back(s1);
                }
            }
        } 
    }
}

bool Pawn::canDoubleStep() {
    if(!hasMoved) { 
        if(pieceColour == WHITE) {
            if(theBoard[position->getX()][position->getY() - 1].getPiece() == nullptr) {
                if(theBoard[position->getX()][position->getY() - 2].getPiece() == nullptr) {
                    return true;
                }
            }
        } else if ( pieceColour == BLACK) {
            if(theBoard[position->getX()][position->getY() + 1].getPiece() == nullptr) {
                if(theBoard[position->getX()][position->getY() + 2].getPiece() == nullptr) {
                    return true;
                }
            }
        }
    }
    return false;
}
