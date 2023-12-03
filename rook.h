#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

// The Rook class is a Piece, and represents the Rook piece in the game

class Rook : public Piece {
    public:
        // Constructor
        Rook(vector<vector<Square>>& board, char pieceType);

        // function that updates the Piece's vector of possible moves it can make,
        // given its location and surrounding pieces.
        void calculateMoves() override;
};

#endif
