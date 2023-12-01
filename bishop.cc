#include "bishop.h"

void Bishop::calculateMoves() {
    possibleMoves.clear();
    blockedMoves.clear();
    
    movesInDir(NE);
    movesInDir(NW);
    movesInDir(SW);
    movesInDir(SE);
}
