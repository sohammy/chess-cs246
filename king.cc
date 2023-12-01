#include "king.h"

vector<Move> King::movesIncludingNonLegal(int x, int y) {
    vector<Move> maybeMoves;
    if(y > 0) {
        if(theBoard->getBoard()[x][y-1].getPiece() == nullptr || theBoard->getBoard()[x][y-1].getPiece()->getColour() != pieceColour) {
            maybeMoves.emplace_back(Move(x,y,x,y-1,N,theBoard->getBoard()[x][y-1]));
        }
    }
    if(y < 7) {
        if(theBoard->getBoard()[x][y+1].getPiece() == nullptr || theBoard->getBoard()[x][y+1].getPiece()->getColour() != pieceColour) {
            maybeMoves.emplace_back(Move(x,y,x,y+1,S,theBoard->getBoard()[x][y+1]));
        }
    }
    if(x > 0){   
        if(theBoard->getBoard()[x-1][y].getPiece() == nullptr || theBoard->getBoard()[x-1][y].getPiece()->getColour() != pieceColour) {
            maybeMoves.emplace_back(Move(x,y,x-1,y,W,theBoard->getBoard()[x-1][y]));
        }
    }    
    if(x < 7) {   
        if(theBoard->getBoard()[x+1][y].getPiece() == nullptr || theBoard->getBoard()[x+1][y].getPiece()->getColour() != pieceColour) {
            maybeMoves.emplace_back(Move(x,y,x+1,y,E,theBoard->getBoard()[x+1][y]));
        }
    }    
    if(y > 0 && x > 0) {   
        if(theBoard->getBoard()[x-1][y-1].getPiece() == nullptr || theBoard->getBoard()[x-1][y-1].getPiece()->getColour() != pieceColour) {
            maybeMoves.emplace_back(Move(x,y,x-1,y-1,NW,theBoard->getBoard()[x-1][y-1]));
        }
    }    
    if(y > 0 && x < 7){   
        if(theBoard->getBoard()[x+1][y-1].getPiece() == nullptr || theBoard->getBoard()[x+1][y-1].getPiece()->getColour() != pieceColour) {
            maybeMoves.emplace_back(Move(x,y,x+1,y-1,NE,theBoard->getBoard()[x+1][y-1]));
        }
    }    
    if(y < 7 && x > 0){       
        if(theBoard->getBoard()[x-1][y+1].getPiece() == nullptr || theBoard->getBoard()[x-1][y+1].getPiece()->getColour() != pieceColour) {
            maybeMoves.emplace_back(Move(x,y,x-1,y+1,SW,theBoard->getBoard()[x-1][y+1]));
        }
    }
    if(y < 7 && x < 7) {
        if(theBoard->getBoard()[x+1][y+1].getPiece() == nullptr || theBoard->getBoard()[x+1][y+1].getPiece()->getColour() != pieceColour) {
            maybeMoves.emplace_back(Move(x,y,x+1,y+1,SE,theBoard->getBoard()[x+1][y+1]));
        }
    }
    return maybeMoves;
}

void King::calculateMoves() {
    possibleMoves.clear();
    blockedMoves.clear();

    int x = position->getX();
    int y = position->getY();
    vector<Move> maybeMoves = movesIncludingNonLegal(x,y);

    if (pieceColour == WHITE) {
        for(Move m: maybeMoves) {
            bool exclusiveToKing = true;

            for(Move n: theBoard->getAliveBlacks()) {
                if(m.isSameDestination(n)) {
                    exclusiveToKing = false;
                    break;
                }
            }

            if(exclusiveToKing) {
                possibleMoves.emplace_back(m);
            }
        }
    } else if (pieceColour == BLACK) {
        for(Move m: maybeMoves) {
            bool exclusiveToKing = true;

            for(Move n: theBoard->getAliveWhites()) {
                if(m.isSameDestination(n)) {
                    exclusiveToKing = false;
                    break;
                }
            }

            if(exclusiveToKing) {
                possibleMoves.emplace_back(m);
            }
        }
    }

}