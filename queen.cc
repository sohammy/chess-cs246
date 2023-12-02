#include "queen.h"

Queen::Queen (vector<vector<Square>>& board, char pieceType) : Piece(board, pieceType) {}

void Queen:: calculateMoves() {
    
    // Clears all irrelevant possible moves, before determining new possible moves
    possibleMoves.clear();
    blockedMoves.clear();
   
    movesInDir(N);
    movesInDir(E);
    movesInDir(S);
    movesInDir(W);
    movesInDir(NE);
    movesInDir(NW);
    movesInDir(SW);
    movesInDir(SE);
}
