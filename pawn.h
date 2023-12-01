#ifndef PAWN_H
#define PAWN_H
#include "piece.h"

class Pawn : public Piece {
    public:
        Pawn(vector<vector<Square>>& board);
        void calculateMoves() override;
        bool canDoubleStep();
};

#endif
