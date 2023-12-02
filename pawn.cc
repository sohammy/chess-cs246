#include "pawn.h"

Pawn::Pawn(vector<vector<Square>>& board, char pieceType): Piece(board, pieceType) {}

void Pawn::calculateMoves() {
    cout << "in pawn" << endl;
    int x = position->getX();
    int y = position->getY();

    possibleMoves.clear();
    blockedMoves.clear();

    bool doubleStep = canDoubleStep();

    if(doubleStep) {
        cout << "YES" << endl;
        if(pieceColour == WHITE) {
            Move s1 = Move(x, y, x, y - 1, N, &theBoard[x][y - 1]);
            Move s2 = Move(x, y, x, y - 2, N, &theBoard[x][y - 2]);
            possibleMoves.emplace_back(s1);
            possibleMoves.emplace_back(s2);
        } else if (pieceColour == BLACK) {
            Move s1 = Move(x, y, x, y + 1, S, &theBoard[x][y + 1]);
            Move s2 = Move(x, y, x, y + 2, S, &theBoard[x][y + 2]);
            possibleMoves.emplace_back(s1);
            possibleMoves.emplace_back(s2);
        }
    } else {
        cout << "NO" << endl;
        if(pieceColour == WHITE) {
            if (y > 0) {
                if(theBoard[x][y - 1].getPiece() == nullptr) {
                    Move s1 = Move(x, y, x, y - 1, N, &theBoard[x][y - 1]);
                    possibleMoves.emplace_back(s1);
                }
            }
        } else if(pieceColour == BLACK) {
            if (y < 7) {
                if(theBoard[x][y + 1].getPiece() == nullptr) {
                    Move s1 = Move(x, y, x, y + 1, S, &theBoard[x][y + 1]);
                    possibleMoves.emplace_back(s1);
                }
            }
        }
    }

    if(pieceColour == WHITE) {
        if (y > 0) {
            if (x < 7) {
                if (theBoard[x + 1][y - 1].getPiece() != nullptr && theBoard[x + 1][y - 1].getPiece()->getColour() != pieceColour) {
                    Move s1 = Move(x, y, x + 1, y - 1, N, &theBoard[x + 1][y - 1]);
                    possibleMoves.emplace_back(s1);
                }
            } else if (x > 0) {
                if (theBoard[x - 1][y - 1].getPiece() != nullptr && theBoard[x - 1][y - 1].getPiece()->getColour() != pieceColour) {
                    Move s1 = Move(x, y, x - 1, y - 1, N, &theBoard[x - 1][y - 1]);
                    possibleMoves.emplace_back(s1);
                }
            }
        } 
    }
    if(pieceColour == BLACK) {
        if (y < 7) {
            if (x < 7) {
                if (theBoard[x + 1][y + 1].getPiece() != nullptr && theBoard[x + 1][y + 1].getPiece()->getColour() != pieceColour) {
                    Move s1 = Move(x, y, x + 1, y + 1, S, &theBoard[x + 1][y + 1]);
                    possibleMoves.emplace_back(s1);
                } else if (theBoard[x + 1][y + 1].canEnPassant()) {
                    Move s1 = Move(x, y, x + 1, y + 1, S, &theBoard[x + 1][y + 1]);
                    possibleMoves.emplace_back(s1);
                }
            } else if (x > 0) {
                if (theBoard[x - 1][y + 1].getPiece() != nullptr && theBoard[x - 1][y + 1].getPiece()->getColour() != pieceColour) {
                    Move s1 = Move(x, y, x - 1, y + 1, S, &theBoard[x - 1][y + 1]);
                    possibleMoves.emplace_back(s1);
                } else if (theBoard[x - 1][y + 1].canEnPassant()) {
                    Move s1 = Move(x, y, x - 1, y + 1, S, &theBoard[x - 1][y + 1]);
                    possibleMoves.emplace_back(s1);
                }
            }
        } 
    }
}

bool Pawn::canDoubleStep() {
    int x = position->getX();
    int y = position->getY();
    if(!hasMoved) { 
        if(pieceColour == WHITE) {
            if(theBoard[x - 1][y].getPiece() == nullptr) {
                if(theBoard[x - 2][y].getPiece() == nullptr) {
                    return true;
                }
            }
        } else if ( pieceColour == BLACK) {
            if(theBoard[x + 1][y].getPiece() == nullptr) {
                if(theBoard[x + 2][y].getPiece() == nullptr) {
                    return true;
                }
            }
        }
    }
    return false;
}
