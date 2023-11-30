#ifndef ROOK_H
#define ROOK_H
#include "piece.h"

class Rook : public Piece {

    bool hasMoved = false; // Used to Determine whether Castling is Permitted

    public:
        void calculateMoves();
};

#endif
