#include "bishop.h"

Bishop::Bishop (vector<vector<Square>>& board, char pieceType) : Piece(board, pieceType)  {}

void Bishop::calculateMoves() {
    possibleMoves.clear();
    blockedMoves.clear();
    
    movesInDir(NE);
    movesInDir(NW);
    movesInDir(SW);
    movesInDir(SE);
}
