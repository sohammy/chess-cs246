#include "knight.h"

void Knight:: calculateMoves () {

    possibleMoves.clear();
    blockedMoves.clear();

    int curX = getX();
    int curY = getY();

    Colour knightColour = getColour();

    if ((curX + 1) <= 7 && (curY - 2) >= 0) { // Right 1, Up 2 (N)
        if (theBoard.getBoard()[curX + 1][curY - 2].getPiece() == nullptr || theBoard.getBoard()[curX + 1][curY - 2].getPiece()->getColour() != knightColour) {
            possibleMoves.emplace_back(Move(curX, curY, curX + 1, curY - 2, NW, &theBoard.getBoard()[curX + 1][curY - 2]));
            theBoard.getBoard()[curX + 1][curY - 2].addPieceObservers(this);
        } else {
            blockedMoves.emplace_back(Move(curX, curY, curX + 1, curY - 2, NW, &theBoard.getBoard()[curX + 1][curY - 2]));
            theBoard.getBoard()[curX + 1][curY - 2].addPieceObservers(this);
        }
    }

    if ((curX + 2) <= 7 && (curY - 1) >= 0) { // Right 2, Up 1 (NE)
        if (theBoard.getBoard()[curX + 2][curY - 1].getPiece() == nullptr || theBoard.getBoard()[curX + 2][curY - 1].getPiece()->getColour() != knightColour) {
            possibleMoves.emplace_back(Move(curX, curY, curX + 2, curY - 1, NE, &theBoard.getBoard()[curX + 2][curY - 1]));
            theBoard.getBoard()[curX + 2][curY - 1].addPieceObservers(this);
        } else {
            blockedMoves.emplace_back(Move(curX, curY, curX + 2, curY - 1, NE, &theBoard.getBoard()[curX + 2][curY - 1]));
            theBoard.getBoard()[curX + 2][curY - 1].addPieceObservers(this);
        }
    }

    if ((curX + 2) <= 7 && (curY + 1) <= 7) { // Right 2, Down 1 (E)
        if (theBoard.getBoard()[curX + 2][curY + 1].getPiece() == nullptr || theBoard.getBoard()[curX + 2][curY + 1].getPiece()->getColour() != knightColour) {
            possibleMoves.emplace_back(Move(curX, curY, curX + 2, curY + 1, E, &theBoard.getBoard()[curX + 2][curY + 1]));
            theBoard.getBoard()[curX + 2][curY + 1].addPieceObservers(this);
        } else {
            blockedMoves.emplace_back(Move(curX, curY, curX + 2, curY + 1, E, &theBoard.getBoard()[curX + 2][curY + 1]));
            theBoard.getBoard()[curX + 2][curY + 1].addPieceObservers(this);
        }
    }

    if ((curX + 1) <= 7 && (curY + 2) <= 7) { // Right 1, Down 2 (SE)
        if (theBoard.getBoard()[curX + 1][curY + 2].getPiece() == nullptr || theBoard.getBoard()[curX + 1][curY + 2].getPiece()->getColour() != knightColour) {
            possibleMoves.emplace_back(Move(curX, curY, curX + 1, curY + 2, SE, &theBoard.getBoard()[curX + 1][curY + 2]));
            theBoard.getBoard()[curX + 1][curY + 2].addPieceObservers(this);
        } else {
            blockedMoves.emplace_back(Move(curX, curY, curX + 1, curY + 2, SE, &theBoard.getBoard()[curX + 1][curY + 2]));
            theBoard.getBoard()[curX + 1][curY + 2].addPieceObservers(this);
        }
    }

    if ((curX - 1) >= 0 && (curY + 2) <= 7) { // Left 1, Down 2 (S)
        if (theBoard.getBoard()[curX - 1][curY + 2].getPiece() == nullptr || theBoard.getBoard()[curX - 1][curY + 2].getPiece()->getColour() != knightColour) {
            possibleMoves.emplace_back(Move(curX, curY, curX - 1, curY + 2, S, &theBoard.getBoard()[curX - 1][curY + 2]));
            theBoard.getBoard()[curX - 1][curY + 2].addPieceObservers(this);
        } else {
            blockedMoves.emplace_back(Move(curX, curY, curX - 1, curY + 2, S, &theBoard.getBoard()[curX - 1][curY + 2]));
            theBoard.getBoard()[curX - 1][curY + 2].addPieceObservers(this);
        }
    }

    if ((curX - 2) >= 0 && (curY + 1) <= 7) { // Left 2, Down 1 (SW)
        if (theBoard.getBoard()[curX - 2][curY + 1].getPiece() == nullptr || theBoard.getBoard()[curX - 2][curY + 1].getPiece()->getColour() != knightColour) {
            possibleMoves.emplace_back(Move(curX, curY, curX - 2, curY + 1, SW, &theBoard.getBoard()[curX - 2][curY + 1]));
            theBoard.getBoard()[curX - 2][curY + 1].addPieceObservers(this);
        } else {
            blockedMoves.emplace_back(Move(curX, curY, curX - 2, curY + 1, SW, &theBoard.getBoard()[curX - 2][curY + 1]));
            theBoard.getBoard()[curX - 2][curY + 1].addPieceObservers(this);
        }
    }

    if ((curX - 2) >= 0 && (curY - 1) >= 0) { // Left 2, Up 1 (W)
        if (theBoard.getBoard()[curX - 2][curY - 1].getPiece() == nullptr || theBoard.getBoard()[curX - 2][curY - 1].getPiece()->getColour() != knightColour) {
            possibleMoves.emplace_back(Move(curX, curY, curX - 2, curY - 1, W, &theBoard.getBoard()[curX - 2][curY - 1]));
            theBoard.getBoard()[curX - 2][curY - 1].addPieceObservers(this);
        } else {
            blockedMoves.emplace_back(Move(curX, curY, curX - 2, curY - 1, W, &theBoard.getBoard()[curX - 2][curY - 1]));
            theBoard.getBoard()[curX][curY-1].addPieceObservers(this);
        }
    }

    if ((curX - 1) >= 0 && (curY - 2) >= 0) { // Left 1, Up 2 (NW)
        if (theBoard.getBoard()[curX - 1][curY - 2].getPiece() == nullptr || theBoard.getBoard()[curX - 1][curY - 2].getPiece()->getColour() != knightColour) {
            possibleMoves.emplace_back(Move(curX, curY, curX - 1, curY - 2, NW, &theBoard.getBoard()[curX - 1][curY - 2]));
            theBoard.getBoard()[curX - 1][curY - 2].addPieceObservers(this);
        } else {
            blockedMoves.emplace_back(Move(curX, curY, curX - 1, curY - 2, NW, &theBoard.getBoard()[curX - 1][curY - 2]));
            theBoard.getBoard()[curX - 1][curY - 2].addPieceObservers(this);
        }
    }

}