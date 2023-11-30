#include "bishop.h"

void Bishop::calculateMoves() {
    movesInDir(NE);
    movesInDir(NW);
    movesInDir(SW);
    movesInDir(SE);
}
