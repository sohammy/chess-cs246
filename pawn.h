#ifndef PAWN_H
#define PAWN_H
#include "piece.h"

class Pawn : public Piece {
    public:
        char getPiece() const override;
        void calculateMoves();
        bool canDoubleStep();
};

#endif
