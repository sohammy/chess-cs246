#include "king.h"

King::King (vector<vector<Square>>& board, char pieceType) : Piece(board, pieceType) {}

vector<Move> King::movesIncludingNonLegal(int x, int y) {
    vector<Move> maybeMoves;
    if(y > 0) {
        if(theBoard[x][y-1].getPiece() == nullptr || theBoard[x][y-1].getPiece()->getColour() != pieceColour) {
            maybeMoves.emplace_back(Move(x,y,x,y-1,&theBoard[x][y-1],W));
        }
    }
    if(y < 7) {
        if(theBoard[x][y+1].getPiece() == nullptr || theBoard[x][y+1].getPiece()->getColour() != pieceColour) {
            maybeMoves.emplace_back(Move(x,y,x,y+1,&theBoard[x][y+1],E));
        }
    }
    if(x > 0){   
        if(theBoard[x-1][y].getPiece() == nullptr || theBoard[x-1][y].getPiece()->getColour() != pieceColour) {
            maybeMoves.emplace_back(Move(x,y,x-1,y,&theBoard[x-1][y],N));
        }
    }    
    if(x < 7) {   
        if(theBoard[x+1][y].getPiece() == nullptr || theBoard[x+1][y].getPiece()->getColour() != pieceColour) {
            maybeMoves.emplace_back(Move(x,y,x+1,y,&theBoard[x+1][y],S));
        }
    }    
    if(y > 0 && x > 0) {   
        if(theBoard[x-1][y-1].getPiece() == nullptr || theBoard[x-1][y-1].getPiece()->getColour() != pieceColour) {
            maybeMoves.emplace_back(Move(x,y,x-1,y-1,&theBoard[x-1][y-1],NW));
        }
    }    
    if(y > 0 && x < 7){   
        if(theBoard[x+1][y-1].getPiece() == nullptr || theBoard[x+1][y-1].getPiece()->getColour() != pieceColour) {
            maybeMoves.emplace_back(Move(x,y,x+1,y-1,&theBoard[x+1][y-1],SW));
        }
    }    
    if(y < 7 && x > 0){       
        if(theBoard[x-1][y+1].getPiece() == nullptr || theBoard[x-1][y+1].getPiece()->getColour() != pieceColour) {
            maybeMoves.emplace_back(Move(x,y,x-1,y+1,&theBoard[x-1][y+1],NE));
        }
    }
    if(y < 7 && x < 7) {
        if(theBoard[x+1][y+1].getPiece() == nullptr || theBoard[x+1][y+1].getPiece()->getColour() != pieceColour) {
            maybeMoves.emplace_back(Move(x,y,x+1,y+1,&theBoard[x+1][y+1],SE));
        }
    }
    return maybeMoves;
}

void King::calculateMoves() {
    cout << "in King" << endl;
    possibleMoves.clear();
    blockedMoves.clear();

    int x = position->getX();
    int y = position->getY();
    vector<Move> maybeMoves = movesIncludingNonLegal(x,y);

    cout << maybeMoves.size() << "number of maybe moves" << endl;
    
    Colour otherTeam;
    if(pieceColour == WHITE) otherTeam = BLACK;
    else otherTeam = WHITE;

    vector<Move> otherTeamsMoves = getTeamsMoves(otherTeam);
    for(Move m: maybeMoves) {
        bool exclusiveToKing = true;
        cout << otherTeamsMoves.size() << "other teams moves" << endl;
        for(Move n: otherTeamsMoves) {
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
