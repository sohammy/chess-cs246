#include "bishop.h"

Bishop::Bishop (vector<vector<Square>>& board, char pieceType) : Piece(board, pieceType)  {}

void Bishop::calculateMoves() {

    // clear the arrays so that only relevant moves are saved
    possibleMoves.clear();
    blockedMoves.clear();
    
    // Sets up possible directions Bishop can move in
    movesInDir(NE);
    movesInDir(NW);
    movesInDir(SW);
    movesInDir(SE);
}
