#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class Rook : public Piece {
    public:
        char getPiece() const override;
        void calculateMoves();
};

#endif
