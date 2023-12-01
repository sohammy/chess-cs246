#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class Queen : public Piece {

public:
    char getPiece() const override;
    void calculateMoves();
};

#endif
