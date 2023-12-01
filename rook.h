#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class Rook : public Piece {
    public:
        Rook(vector<vector<Square>>& board);
        void calculateMoves() override;
};

#endif
