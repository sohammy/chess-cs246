#include "rook.h"

void Rook::calculateMoves() {
    possibleMoves.clear();
    blockedMoves.clear();
    
    movesInDir(N);
    movesInDir(E);
    movesInDir(S);
    movesInDir(W);
    // Add Castling Functionality
}

