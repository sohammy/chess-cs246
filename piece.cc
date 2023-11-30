#include "piece.h"

void Piece::setColour(char c) {
    if (c == 'w') pieceColour = WHITE;
    if (c == 'b') pieceColour = BLACK;
}

void Piece::notify(Square& s) {
    bool isInPossibleMoves = true;
    Direction d;
    for(Move m : blockedMoves) {
        if(m.getSquare() == &s) {
            d = m.getDirection();
            isInPossibleMoves = false; 
            break; 
        }
    }

    if(isInPossibleMoves) {
        for(Move m : possibleMoves) {
            if(m.getSquare() == &s) {
                d = m.getDirection();
                break;
            }
        }
    }
    
    if(isInPossibleMoves) {
        if(d == N) {
            
        } else if (d == E) {

        } else if (d == S) {

        } else if (d == W) {

        } else if (d == NE) {

        } else if (d == NW) {

        } else if (d == SE) {

        } else if (d == SW) {

        }
    } else {
        if(d == N) {
            
        } else if (d == E) {

        } else if (d == S) {

        } else if (d == W) {

        } else if (d == NE) {

        } else if (d == NW) {

        } else if (d == SE) {

        } else if (d == SW) {

        }
    }

}
