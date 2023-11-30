#include "queen.h"

void Queen:: calculateMoves() {
    movesInDir(N);
    movesInDir(E);
    movesInDir(S);
    movesInDir(W);
    movesInDir(NE);
    movesInDir(NW);
    movesInDir(SW);
    movesInDir(SE);
}