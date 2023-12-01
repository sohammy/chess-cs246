#ifndef KING_H
#define KING_H

#include "piece.h"

class King : public Piece {
    vector<Move> movesIncludingNonLegal(int x, int y);
    public:
        King (vector<vector<Square>>& board, char pieceType);
        void calculateMoves() override;
};

#endif
