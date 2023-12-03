#include "king.h"

King::King (vector<vector<Square>>& board, char pieceType) : Piece(board, pieceType) {}

vector<Move> King::movesIncludingNonLegal(int x, int y) {

    // vector of moves the King could potentially make
    vector<Move> maybeMoves;

    if(y > 0) { // Check if King can potentially move South one square
        if(theBoard[x][y-1].getPiece() == nullptr || theBoard[x][y-1].getPiece()->getColour() != pieceColour) {
            maybeMoves.emplace_back(Move(x,y,x,y-1,&theBoard[x][y-1],W));
        }
    }
    if(y < 7) { // Check if King can potentially move North one square
        if(theBoard[x][y+1].getPiece() == nullptr || theBoard[x][y+1].getPiece()->getColour() != pieceColour) {
            maybeMoves.emplace_back(Move(x,y,x,y+1,&theBoard[x][y+1],E));
        }
    }
    if(x > 0){ // Check if King can potentially move West one square
        if(theBoard[x-1][y].getPiece() == nullptr || theBoard[x-1][y].getPiece()->getColour() != pieceColour) {
            maybeMoves.emplace_back(Move(x,y,x-1,y,&theBoard[x-1][y],N));
        }
    }    
    if(x < 7) { // Check if king can potentially move East one square
        if(theBoard[x+1][y].getPiece() == nullptr || theBoard[x+1][y].getPiece()->getColour() != pieceColour) {
            maybeMoves.emplace_back(Move(x,y,x+1,y,&theBoard[x+1][y],S));
        }
    }    
    if(y > 0 && x > 0) { // Check if king can potentially move SouthWest one square
        if(theBoard[x-1][y-1].getPiece() == nullptr || theBoard[x-1][y-1].getPiece()->getColour() != pieceColour) {
            maybeMoves.emplace_back(Move(x,y,x-1,y-1,&theBoard[x-1][y-1],NW));
        }
    }    
    if(y > 0 && x < 7){ // Check if king can potentially move SouthEast one square
        if(theBoard[x+1][y-1].getPiece() == nullptr || theBoard[x+1][y-1].getPiece()->getColour() != pieceColour) {
            maybeMoves.emplace_back(Move(x,y,x+1,y-1,&theBoard[x+1][y-1],SW));
        }
    }    
    if(y < 7 && x > 0){ // Check if king can potentially move NorthWest one square
        if(theBoard[x-1][y+1].getPiece() == nullptr || theBoard[x-1][y+1].getPiece()->getColour() != pieceColour) {
            maybeMoves.emplace_back(Move(x,y,x-1,y+1,&theBoard[x-1][y+1],NE));
        }
    }
    if(y < 7 && x < 7) { // Check if king can potentially move NorthEast one square
        if(theBoard[x+1][y+1].getPiece() == nullptr || theBoard[x+1][y+1].getPiece()->getColour() != pieceColour) {
            maybeMoves.emplace_back(Move(x,y,x+1,y+1,&theBoard[x+1][y+1],SE));
        }
    }
    return maybeMoves;
}

void King::calculateMoves() {
    // clear the arrays so that only relevant moves are saved
    possibleMoves.clear();
    blockedMoves.clear();

    // set x and y to King's current x and y coordinates
    int x = position->getX();
    int y = position->getY();
    vector<Move> maybeMoves = movesIncludingNonLegal(x,y);
    
    Colour otherTeam;
    if(pieceColour == WHITE) otherTeam = BLACK;
    else otherTeam = WHITE;

    vector<Move> otherTeamsMoves = getTeamsMoves(otherTeam); // for other teams king, just return all the possilbe moves it could make, not depeding on this kings move
    vector<Move> otherTeamsBlockedMoves = getTeamsBlockedMoves(otherTeam);

    // Check whether any of the moves in maybeMoves is unsafe (opponent can kill)
    int index = 0;
    for(Move m: maybeMoves) {
        bool exclusiveToKing = true;
        for(Move n: otherTeamsMoves) {
            if(m.isSameDestination(n)) {
                exclusiveToKing = false;
                break;
            }
        }

        for(Move n: otherTeamsBlockedMoves) {
            if(m.isSameDestination(n)) {
                exclusiveToKing = false;
                break;
            }
        }
        // if the move is safe, emplace it in the vector possibleMoves
        if(exclusiveToKing) {
            possibleMoves.emplace_back(m);
        }
        ++index;
    }
}

char King::checkMate() {
    Colour otherTeam;
    if(pieceColour == WHITE) otherTeam = BLACK;
    else otherTeam = WHITE;

    vector<Piece*> otherTeamPieces = getTeamOfColour(otherTeam);
    
    vector<Move> checkingKingMoves;
    vector<Piece*> piecesCheckingKing;

    for(Piece* p : otherTeamPieces) {
        p->calculateMoves();
        vector<Move> thisPiecesMoves = p->getMoves();

        for(Move m : thisPiecesMoves) {
            if(m.getDestX() == position->getX() && m.getDestY() == position->getY()) {
                checkingKingMoves.emplace_back(m);
                piecesCheckingKing.emplace_back(p);
            }
        }
    }

    cout << piecesCheckingKing.size() << checkingKingMoves.size() << endl;

    // Everything up to here is seeing what is dangerous to the King at the moment

    calculateMoves();
    int numberOfAttackers = piecesCheckingKing.size();

    cout << numberOfAttackers << endl;

    if (numberOfAttackers == 1) {
        if(possibleMoves.size() == 0) { // If king can't move haha

            Piece* attackingPiece = piecesCheckingKing[0];
            vector<Move> ourTeamsMoves = getTeamsMoves(pieceColour);
            vector<Move> ourTeamsMovesWithoutKing;
            for(Move m: ourTeamsMoves) { // If we can take the piece that's attacking
                if(m.getDestX() == attackingPiece->getX() && m.getDestY() == attackingPiece->getY()) {
                    if(m.getInitX() != getX() && m.getInitY() != getY()) {
                        return 'C';
                    }
                }
                if(m.getInitX() != getX() && m.getInitY() != getY()) ourTeamsMovesWithoutKing.emplace_back(m);
            }

            vector<Move> attackersMoves = attackingPiece->getMoves();
            Direction attackDirection = checkingKingMoves[0].getDirection();
            vector<Move> attackMovesTowardsKing;

            for(Move m : attackersMoves) {
                if(m.getDirection() == attackDirection) {
                    attackMovesTowardsKing.emplace_back(m);
                }
            }

            for(Move m : attackMovesTowardsKing) { // If we can block
                for(Move n : ourTeamsMovesWithoutKing) {
                    if(m.isSameDestination(n)) {
                        return 'C';
                    }
                }
            }
            return 'M';
        } else {
            return 'C';
        }

    } else if (numberOfAttackers > 1) {
        if(possibleMoves.size() == 0) {
            return 'M';
        }
    }

    return 'N';
}