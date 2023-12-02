#include "rook.h"

Rook::Rook(vector<vector<Square>>& board, char pieceType) : Piece(board, pieceType) {}

void Rook::calculateMoves() {
    cout << "in Rook" << endl;
    possibleMoves.clear();
    blockedMoves.clear();
    
    movesInDir(N);
    movesInDir(E);
    movesInDir(S);
    movesInDir(W);

    cout << possibleMoves.size() << endl;
    // Add Castling Functionality
}
