#include "bishop.h"

Bishop::Bishop (vector<vector<Square>>& board, char pieceType) : Piece(board, pieceType)  {}

void Bishop::calculateMoves() {
    cout << "in bishop" << endl;
    possibleMoves.clear();
    blockedMoves.clear();
    
    movesInDir(NE);
    movesInDir(NW);
    movesInDir(SW);
    movesInDir(SE);
}
