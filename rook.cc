#include "rook.h"

void Rook::calculateMoves() {
    movesInDir(N);
    movesInDir(E);
    movesInDir(S);
    movesInDir(W);

    // Add Castling Functionality
}

