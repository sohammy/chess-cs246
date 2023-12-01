#include "bishop.h"

Bishop::Bishop (vector<vector<Square>>& board) : Piece(board) {}

void Bishop::calculateMoves() {
    possibleMoves.clear();
    blockedMoves.clear();
    
    movesInDir(NE);
    movesInDir(NW);
    movesInDir(SW);
    movesInDir(SE);
}
