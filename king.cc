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

    vector<Move> otherTeamsMoves = getTeamsMoves(otherTeam);

     // Check whether any of the moves in maybeMoves is unsafe (opponent can kill)
    for(Move m: maybeMoves) {
        bool exclusiveToKing = true;
        for(Move n: otherTeamsMoves) {
            if(m.isSameDestination(n)) {
                exclusiveToKing = false;
                break;
            }
        }
        // if the move is safe, emplace it in the vector possibleMoves
        if(exclusiveToKing) {
            possibleMoves.emplace_back(m);
        }
    }
}

// bool King::checkMate() {

//     bool KingCannotMove = false;
//     bool CanKillToSave = false;
//     bool CanBlockToSave = false;

//     if (getMoves().size() == 0) {
//         KingCannotMove = true;
//     }

//     // for each opp piece that is about to kill king, see if there is a friendly piece that can kill it

//     for (Piece p: )

// }
