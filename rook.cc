#include "rook.h"

Rook::Rook(vector<vector<Square>>& board) : Piece(board) {}

void Rook::calculateMoves() {
    possibleMoves.clear();
    blockedMoves.clear();
    
    movesInDir(N);
    movesInDir(E);
    movesInDir(S);
    movesInDir(W);
    // Add Castling Functionality
}

