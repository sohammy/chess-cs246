#include "queen.h"

Queen::Queen (vector<vector<Square>>& board) : Piece(board) {}

void Queen:: calculateMoves() {
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