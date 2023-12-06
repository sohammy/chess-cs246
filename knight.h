#ifndef KNIGHT_H
#define KNIGHT_H
#include "piece.h"

// The Knight class is a Piece, and represents the Knight piece in the game

class Knight : public Piece {
    public:

        // Constructor
        Knight (vector<vector<Square>>& board, char pieceType);

        // Function that updates the Piece's vector of possible moves it can make,
        // given its location and surrounding pieces.
        void calculateMoves() override;
};

#endif
