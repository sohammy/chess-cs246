#include "pawn.h"

void Pawn::calculateMoves() {

    possibleMoves.clear();
    blockedMoves.clear();

    Colour pawnColour = getColour();
    int curX = getX();
    int curY = getY();

    if (hasMoved) {
        doubleStep = false;
    }

    if (pawnColour == WHITE) {

        bool canMoveOne = false;

        if ((curY - 1) >= 0) {
            
                
        }

        if ((curY - 1) >= 0 && (curX - 1) >= 0) {

        }

        if ((curY - 1) >= 0 && (curX + 1) <= 7) {

        }

        if (doubleStep && ) {
            if ((curY - 2) >= 0) { // Checks if In Range
                if (theBoard->getBoard()[curX][curY - 1]->getPiece() == nullptr) { // Checks if Pawn can move UP by ONE MOVE
                    possibleMoves.emplace_back(Move(curX, curY, curX, curY - 1, N, theBoard->getBoard()[curX][curY-1]));
                    theBoard->getBoard()[curX][curY-1]->addPieceObservers(this);

                    if (theBoard->getBoard()[curX][curY - 2]->getPiece() == nullptr) { // Checks if Pawn can move UP by TWO MOVES
                        possibleMoves.emplace_back(Move(curX, curY, curX, curY - 2, N, theBoard->getBoard()[curX][curY-2]));
                        theBoard->getBoard()[curX][curY-2]->addPieceObservers(this);
                    } else {
                        blockedMoves.emplace_back(Move(curX, curY, curX, curY - 2, N, theBoard->getBoard()[curX][curY-2]));
                        theBoard->getBoard()[curX][curY-2]->addPieceObservers(this);
                    }
                } else {
                    blockedMoves.emplace_back(Move(curX, curY, curX, curY - 1, N, theBoard->getBoard()[curX][curY-1]));
                    theBoard->getBoard()[curX][curY-1]->addPieceObservers(this);
                }
            }
        }

    } else if (pawnColour == BLACK) {

        if ((curY + 1) <= 0) {
            
        }

        if ((curY + 1) <= 0 && (curX - 1) >= 0) {

        }

        if ((curY + 1) <= 0 && (curX + 1) <= 7) {

        }

        if (doubleStep) {
            if ((curY + 2) <= 7) { // Checks if In Range
                if (theBoard->getBoard()[curX][curY + 1]->getPiece() == nullptr) { // Checks if Pawn can move UP by ONE MOVE
                    possibleMoves.emplace_back(Move(curX, curY, curX, curY + 1, N, theBoard->getBoard()[curX][curY+1]));
                    theBoard->getBoard()[curX][curY+1]->addPieceObservers(this);
                    if (theBoard->getBoard()[curX][curY + 2]->getPiece() == nullptr) { // Checks if Pawn can move UP by TWO MOVES
                        possibleMoves.emplace_back(Move(curX, curY, curX, curY + 2, N, theBoard->getBoard()[curX][curY+2]));
                        theBoard->getBoard()[curX][curY+2]->addPieceObservers(this);
                    } else {
                        blockedMoves.emplace_back(Move(curX, curY, curX, curY + 2, N, theBoard->getBoard()[curX][curY+2]));
                        theBoard->getBoard()[curX][curY+2]->addPieceObservers(this);
                    }
                } else {
                    blockedMoves.emplace_back(Move(curX, curY, curX, curY + 1, N, theBoard->getBoard()[curX][curY+1]));
                    theBoard->getBoard()[curX][curY+1]->addPieceObservers(this);
                }
            }
        }

        }




    }
}