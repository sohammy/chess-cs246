#ifndef PAWN_H
#define PAWN_H
#include "piece.h"

class Pawn : public Piece {
    public:

        // Constructor
        Pawn(vector<vector<Square>>& board, char pieceType);

        // function that updates the Piece's vector of possible moves it can make,
        // given its location and surrounding pieces.
        void calculateMoves() override;

        // Checks whether a Pawn is able to Double Step
        bool canDoubleStep();
};

#endif
