#include "king.h"

King::King (vector<vector<Square>>& board, char pieceType) : Piece(board, pieceType) {}

vector<Move> King::movesIncludingNonLegal(int x, int y) {

    // vector of moves the King could potentially make
    vector<Move> maybeMoves;

    if(y > 0) { // Check if King can potentially move South one square
        if(theBoard[x][y-1].getPiece() == nullptr || theBoard[x][y-1].getPiece()->getColour() != pieceColour) {
            maybeMoves.emplace_back(Move(x,y,x,y-1,&theBoard[x][y-1],W));
        } else {
            blockedMoves.emplace_back(Move(x,y,x,y-1,&theBoard[x][y-1],W));
        }
    }
    if(y < 7) { // Check if King can potentially move North one square
        if(theBoard[x][y+1].getPiece() == nullptr || theBoard[x][y+1].getPiece()->getColour() != pieceColour) {
            maybeMoves.emplace_back(Move(x,y,x,y+1,&theBoard[x][y+1],E));
        } else {
            blockedMoves.emplace_back(Move(x,y,x,y+1,&theBoard[x][y+1],E));
        }
    }
    if(x > 0){ // Check if King can potentially move West one square
        if(theBoard[x-1][y].getPiece() == nullptr || theBoard[x-1][y].getPiece()->getColour() != pieceColour) {
            maybeMoves.emplace_back(Move(x,y,x-1,y,&theBoard[x-1][y],N));
        } else {
            blockedMoves.emplace_back(Move(x,y,x-1,y,&theBoard[x-1][y],N));
        }
    }    
    if(x < 7) { // Check if king can potentially move East one square
        if(theBoard[x+1][y].getPiece() == nullptr || theBoard[x+1][y].getPiece()->getColour() != pieceColour) {
            maybeMoves.emplace_back(Move(x,y,x+1,y,&theBoard[x+1][y],S));
        } else {
            blockedMoves.emplace_back(Move(x,y,x+1,y,&theBoard[x+1][y],S));
        }
    }    
    if(y > 0 && x > 0) { // Check if king can potentially move SouthWest one square
        if(theBoard[x-1][y-1].getPiece() == nullptr || theBoard[x-1][y-1].getPiece()->getColour() != pieceColour) {
            maybeMoves.emplace_back(Move(x,y,x-1,y-1,&theBoard[x-1][y-1],NW));
        } else {
            blockedMoves.emplace_back(Move(x,y,x-1,y-1,&theBoard[x-1][y-1],NW));
        }
    }    
    if(y > 0 && x < 7){ // Check if king can potentially move SouthEast one square
        if(theBoard[x+1][y-1].getPiece() == nullptr || theBoard[x+1][y-1].getPiece()->getColour() != pieceColour) {
            maybeMoves.emplace_back(Move(x,y,x+1,y-1,&theBoard[x+1][y-1],SW));
        } else {
            blockedMoves.emplace_back(Move(x,y,x+1,y-1,&theBoard[x+1][y-1],SW));
        }
    }    
    if(y < 7 && x > 0){ // Check if king can potentially move NorthWest one square
        if(theBoard[x-1][y+1].getPiece() == nullptr || theBoard[x-1][y+1].getPiece()->getColour() != pieceColour) {
            maybeMoves.emplace_back(Move(x,y,x-1,y+1,&theBoard[x-1][y+1],NE));
        } else {
            blockedMoves.emplace_back(Move(x,y,x-1,y+1,&theBoard[x-1][y+1],NE));
        }
    }
    if(y < 7 && x < 7) { // Check if king can potentially move NorthEast one square
        if(theBoard[x+1][y+1].getPiece() == nullptr || theBoard[x+1][y+1].getPiece()->getColour() != pieceColour) {
            maybeMoves.emplace_back(Move(x,y,x+1,y+1,&theBoard[x+1][y+1],SE));
        } else {
            blockedMoves.emplace_back(Move(x,y,x+1,y+1,&theBoard[x+1][y+1],SE));
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

    canCastleShort();
    canCastleLong();

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

    // Everything up to here is seeing what is dangerous to the King at the moment

    calculateMoves();
    int numberOfAttackers = piecesCheckingKing.size();

    if (numberOfAttackers == 1) {
        if(possibleMoves.size() == 0) { // If the King CAN'T Move
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
        } else {
            return 'C';
        }
    }

    return 'N';
}

bool King::canCastleShort() {
    if (!hasMoved) {
        if (getColour() == Colour::WHITE && position->getX() == 7 && position->getY() == 4) {
            if (theBoard[7][5].getPiece() == nullptr && theBoard[7][6].getPiece() == nullptr && theBoard[7][7].getPiece() != nullptr) { // Checks for No Spaces in Between
                if (theBoard[7][7].getPiece()->getPieceName() == 'R') { // Checks Rook is at the End
                    if (theBoard[7][7].getPiece()->hasItMoved() == false) { // Checks that Rook hasn't Moved
                        ////
                        for (Piece* p : getTeamOfColour(Colour::BLACK)) {
                            for (unsigned int i = 0; i < p->getMoves().size(); ++i) {
                                if (p->getMoves()[i].getDestY() == 4 && p->getMoves()[i].getDestX() == 7) { // Is it in Check in Current Square
                                    return false;
                                } else if (p->getMoves()[i].getDestY() == 5 && p->getMoves()[i].getDestX() == 7) { // Checks if in Check in Space Between
                                    return false;
                                } else if (p->getMoves()[i].getDestY() == 6 && p->getMoves()[i].getDestX() == 7) { // Is it in Check in Ending Square
                                    return false;
                                }
                            }
                        }
                        ////
                        Move m {"e1", "g1", theBoard};
                        possibleMoves.emplace_back(m);
                        //  It Can Castle!
                        return true; // NOT IN CHECK ANYWHERE IN THE PATH!
                    }
                    return false;
                }
                return false;
            }
            return false;
        } 
        
        else if (getColour() == Colour::BLACK && position->getX() == 0 && position->getY() == 4) {
            if (theBoard[0][5].getPiece() == nullptr && theBoard[0][6].getPiece() == nullptr && theBoard[0][7].getPiece() != nullptr) { // Checks for No Spaces in Between
                if (theBoard[0][7].getPiece()->getPieceName() == 'r') { // Checks Rook is at the End
                    if (theBoard[0][7].getPiece()->hasItMoved() == false) { // Checks that Rook hasn't moved
                        ////
                        for (Piece* p : getTeamOfColour(Colour::WHITE)) {
                            for (unsigned int i = 0; i < p->getMoves().size(); ++i) {
                                if (p->getMoves()[i].getDestY() == 4 && p->getMoves()[i].getDestX() == 0) { // Is it in Check in Current Square
                                    return false;
                                } else if (p->getMoves()[i].getDestY() == 5 && p->getMoves()[i].getDestX() == 0) { // Checks if in Check in Space Between
                                    return false;
                                } else if (p->getMoves()[i].getDestY() == 6 && p->getMoves()[i].getDestX() == 0) { // Is it in Check in Ending Square
                                    return false;
                                }
                            }
                        }
                        ////
                        Move m {"e8", "g8", theBoard};
                        possibleMoves.emplace_back(m);
                        //  It Can Castle!
                        return true; // NOT IN CHECK ANYWHERE IN THE PATH!
                    }
                }
                return false;
            }
            return false;
        }
    }
    return false;
}

bool King::canCastleLong() {
    if (!hasMoved) {
        if (getColour() == Colour::WHITE && position->getX() == 7 && position->getY() == 4) {
            if (theBoard[7][3].getPiece() == nullptr && theBoard[7][2].getPiece() == nullptr && theBoard[7][1].getPiece() == nullptr && theBoard[7][0].getPiece() != nullptr) { // Checks for No Spaces in Between
                if (theBoard[7][0].getPiece()->getPieceName() == 'R') { // Checks Rook is at the End
                    if (theBoard[7][0].getPiece()->hasItMoved() == false) { // Checks that Rook hasn't Moved
                        //////
                        for (Piece* p : getTeamOfColour(Colour::BLACK)) {
                            for (unsigned int i = 0; i < p->getMoves().size(); ++i) {
                                if (p->getMoves()[i].getDestY() == 4 && p->getMoves()[i].getDestX() == 7) { // Is it in Check in Current Square
                                    return false;
                                } else if (p->getMoves()[i].getDestY() == 3 && p->getMoves()[i].getDestX() == 7) { // Checks if in Check in Space Between
                                    return false;
                                } else if (p->getMoves()[i].getDestY() == 2 && p->getMoves()[i].getDestX() == 7) { // Is it in Check in Ending Square
                                    return false;
                                }
                            }
                        }
                        //////
                        Move m {"e1", "c1", theBoard};
                        possibleMoves.emplace_back(m);
                        //  It Can Castle!
                        return true; // NOT IN CHECK ANYWHERE IN THE PATH!
                    }
                    return false;
                }
                return false;
            }
            return false;
        } 
        
        else if (getColour() == Colour::BLACK && position->getX() == 0 && position->getY() == 4) {
            if (theBoard[0][3].getPiece() == nullptr && theBoard[0][2].getPiece() == nullptr && theBoard[0][1].getPiece() == nullptr && theBoard[0][0].getPiece() != nullptr) { // Checks for No Spaces in Between
                if (theBoard[0][0].getPiece()->getPieceName() == 'r') { // Checks Rook is at the End
                    if (theBoard[0][0].getPiece()->hasItMoved() == false) { // Checks that Rook hasn't moved
                    ////
                    for (Piece* p : getTeamOfColour(Colour::WHITE)) {
                        for (unsigned int i = 0; i < p->getMoves().size(); ++i) {
                            if (p->getMoves()[i].getDestY() == 4 && p->getMoves()[i].getDestX() == 0) { // Is it in Check in Current Square
                                return false;
                            } else if (p->getMoves()[i].getDestY() == 3 && p->getMoves()[i].getDestX() == 0) { // Checks if in Check in Space Between
                                return false;
                            } else if (p->getMoves()[i].getDestY() == 2 && p->getMoves()[i].getDestX() == 0) { // Is it in Check in Ending Square
                                return false;
                            }
                        }
                    }
                    ////
                        Move m {"e8", "c8", theBoard};
                        possibleMoves.emplace_back(m);
                        //  It Can Castle!
                        return true; // NOT IN CHECK ANYWHERE IN THE PATH!
                    }
                }
                return false;
            }
            return false;
        }
    }
    return false;
}
