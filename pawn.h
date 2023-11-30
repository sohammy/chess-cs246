#ifndef PAWN_H
#define PAWN_H
#include "piece.h"

class Pawn : public Piece {
    bool doubleStep = true;

    public:
        void calculateMoves();
        bool canDoubleStep();
};

#endif
