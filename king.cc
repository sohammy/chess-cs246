#include "king.h"

vector<Move> King::movesIncludingNonLegal(int x, int y) {
    vector<Move> maybeMoves;
    if(theBoard->getBoard()[x][y-1].getPiece() != nullptr && theBoard->getBoard()[x][y-1].getPiece()->getColour() != pieceColour) {
        if(y > 0) maybeMoves.emplace_back(Move(x,y,x,y-1,N,theBoard->getBoard()[x][y-1]));
    }
    if(theBoard->getBoard()[x][y+1].getPiece() != nullptr && theBoard->getBoard()[x][y+1].getPiece()->getColour() != pieceColour) {
        if(y < 7) maybeMoves.emplace_back(Move(x,y,x,y+1,S,theBoard->getBoard()[x][y+1]));
    }
    if(theBoard->getBoard()[x-1][y].getPiece() != nullptr && theBoard->getBoard()[x-1][y].getPiece()->getColour() != pieceColour){   
        if(x > 0) maybeMoves.emplace_back(Move(x,y,x-1,y,W,theBoard->getBoard()[x-1][y]));
    }    
    if(theBoard->getBoard()[x+1][y].getPiece() != nullptr && theBoard->getBoard()[x+1][y].getPiece()->getColour() != pieceColour) {   
        if(x < 7) maybeMoves.emplace_back(Move(x,y,x+1,y,E,theBoard->getBoard()[x+1][y]));
    }    
    if(theBoard->getBoard()[x-1][y-1].getPiece() != nullptr && theBoard->getBoard()[x-1][y-1].getPiece()->getColour() != pieceColour) {   
        if(y > 0 && x > 0) maybeMoves.emplace_back(Move(x,y,x-1,y-1,NW,theBoard->getBoard()[x-1][y-1]));
    }    
    if(theBoard->getBoard()[x+1][y-1].getPiece() != nullptr && theBoard->getBoard()[x+1][y-1].getPiece()->getColour() != pieceColour){   
        if(y > 0 && x < 7) maybeMoves.emplace_back(Move(x,y,x+1,y-1,NE,theBoard->getBoard()[x+1][y-1]));
    }    
    if(theBoard->getBoard()[x-1][y+1].getPiece() != nullptr && theBoard->getBoard()[x-1][y+1].getPiece()->getColour() != pieceColour){       
        if(y < 7 && x > 0) maybeMoves.emplace_back(Move(x,y,x-1,y+1,SW,theBoard->getBoard()[x-1][y+1]));
    }
    if(theBoard->getBoard()[x+1][y+1].getPiece() != nullptr && theBoard->getBoard()[x+1][y+1].getPiece()->getColour() != pieceColour){
        if(y < 7 && x < 7) maybeMoves.emplace_back(Move(x,y,x+1,y+1,SE,theBoard->getBoard()[x+1][y+1]));
    }
    return maybeMoves;
}

void King::calculateMoves() {
    int x = position->getX();
    int y = position->getY();
    vector<Move> maybeMoves = movesIncludingNonLegal(x,y);

    

}