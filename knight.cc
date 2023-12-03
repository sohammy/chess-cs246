#include "knight.h"

Knight :: Knight (vector<vector<Square>>& board, char pieceType) : Piece(board, pieceType) {}

void Knight:: calculateMoves () {
    
    // Clear out all previous possible moves 
    possibleMoves.clear();
    blockedMoves.clear();

    int curX = getX();
    int curY = getY();

    Colour knightColour = getColour();

    if ((curX + 1) <= 7 && (curY - 2) >= 0) { // Right 1, Up 2 (SW)
        if (theBoard[curX + 1][curY - 2].getPiece() == nullptr || theBoard[curX + 1][curY - 2].getPiece()->getColour() != knightColour) {
            possibleMoves.emplace_back(Move(curX, curY, curX + 1, curY - 2, &theBoard[curX + 1][curY - 2], SW));
            theBoard[curX + 1][curY - 2].addPieceObservers(this);
        } else {
            blockedMoves.emplace_back(Move(curX, curY, curX + 1, curY - 2, &theBoard[curX + 1][curY - 2], SW));
            theBoard[curX + 1][curY - 2].addPieceObservers(this);
        }
    }

    if ((curX + 2) <= 7 && (curY - 1) >= 0) { // Right 2, Up 1 (SW)
        if (theBoard[curX + 2][curY - 1].getPiece() == nullptr || theBoard[curX + 2][curY - 1].getPiece()->getColour() != knightColour) {
            possibleMoves.emplace_back(Move(curX, curY, curX + 2, curY - 1, &theBoard[curX + 2][curY - 1], SW));
            theBoard[curX + 2][curY - 1].addPieceObservers(this);
        } else {
            blockedMoves.emplace_back(Move(curX, curY, curX + 2, curY - 1, &theBoard[curX + 2][curY - 1], SW));
            theBoard[curX + 2][curY - 1].addPieceObservers(this);
        }
    }

    if ((curX + 2) <= 7 && (curY + 1) <= 7) { // Right 2, Down 1 (SE)
        if (theBoard[curX + 2][curY + 1].getPiece() == nullptr || theBoard[curX + 2][curY + 1].getPiece()->getColour() != knightColour) {
            possibleMoves.emplace_back(Move(curX, curY, curX + 2, curY + 1, &theBoard[curX + 2][curY + 1], SE));
            theBoard[curX + 2][curY + 1].addPieceObservers(this);
        } else {
            blockedMoves.emplace_back(Move(curX, curY, curX + 2, curY + 1, &theBoard[curX + 2][curY + 1], SE));
            theBoard[curX + 2][curY + 1].addPieceObservers(this);
        }
    }

    if ((curX + 1) <= 7 && (curY + 2) <= 7) { // Right 1, Down 2 (SE)
        if (theBoard[curX + 1][curY + 2].getPiece() == nullptr || theBoard[curX + 1][curY + 2].getPiece()->getColour() != knightColour) {
            possibleMoves.emplace_back(Move(curX, curY, curX + 1, curY + 2, &theBoard[curX + 1][curY + 2], SE));
            theBoard[curX + 1][curY + 2].addPieceObservers(this);
        } else {
            blockedMoves.emplace_back(Move(curX, curY, curX + 1, curY + 2, &theBoard[curX + 1][curY + 2], SE));
            theBoard[curX + 1][curY + 2].addPieceObservers(this);
        }
    }

    if ((curX - 1) >= 0 && (curY + 2) <= 7) { // Left 1, Down 2 (NE)
        if (theBoard[curX - 1][curY + 2].getPiece() == nullptr || theBoard[curX - 1][curY + 2].getPiece()->getColour() != knightColour) {
            possibleMoves.emplace_back(Move(curX, curY, curX - 1, curY + 2, &theBoard[curX - 1][curY + 2], NE));
            theBoard[curX - 1][curY + 2].addPieceObservers(this);
        } else {
            blockedMoves.emplace_back(Move(curX, curY, curX - 1, curY + 2, &theBoard[curX - 1][curY + 2], NE));
            theBoard[curX - 1][curY + 2].addPieceObservers(this);
        }
    }

    if ((curX - 2) >= 0 && (curY + 1) <= 7) { // Left 2, Down 1 (NE)
        if (theBoard[curX - 2][curY + 1].getPiece() == nullptr || theBoard[curX - 2][curY + 1].getPiece()->getColour() != knightColour) {
            possibleMoves.emplace_back(Move(curX, curY, curX - 2, curY + 1, &theBoard[curX - 2][curY + 1], NE));
            theBoard[curX - 2][curY + 1].addPieceObservers(this);
        } else {
            blockedMoves.emplace_back(Move(curX, curY, curX - 2, curY + 1, &theBoard[curX - 2][curY + 1], NE));
            theBoard[curX - 2][curY + 1].addPieceObservers(this);
        }
    }

    if ((curX - 2) >= 0 && (curY - 1) >= 0) { // Left 2, Up 1 (NW)
        if (theBoard[curX - 2][curY - 1].getPiece() == nullptr || theBoard[curX - 2][curY - 1].getPiece()->getColour() != knightColour) {
            possibleMoves.emplace_back(Move(curX, curY, curX - 2, curY - 1, &theBoard[curX - 2][curY - 1], NW));
            theBoard[curX - 2][curY - 1].addPieceObservers(this);
        } else {
            blockedMoves.emplace_back(Move(curX, curY, curX - 2, curY - 1, &theBoard[curX - 2][curY - 1], NW));
            theBoard[curX - 2][curY-1].addPieceObservers(this);
        }
    }

    if ((curX - 1) >= 0 && (curY - 2) >= 0) { // Left 1, Up 2 (NW)
        if (theBoard[curX - 1][curY - 2].getPiece() == nullptr || theBoard[curX - 1][curY - 2].getPiece()->getColour() != knightColour) {
            possibleMoves.emplace_back(Move(curX, curY, curX - 1, curY - 2, &theBoard[curX - 1][curY - 2], NW));
            theBoard[curX - 1][curY - 2].addPieceObservers(this);
        } else {
            blockedMoves.emplace_back(Move(curX, curY, curX - 1, curY - 2, &theBoard[curX - 1][curY - 2], NW));
            theBoard[curX - 1][curY - 2].addPieceObservers(this);
        }
    }
}
