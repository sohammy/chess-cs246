#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Knight : public Piece {
    public:
        char getPiece() const override;
        void calculateMoves();
};


#endif
