#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

// The Queen class is a Piece, and represents the Queen piece in the game

class Queen : public Piece {

public:

    // Contructor
    Queen (vector<vector<Square>>& board, char pieceType);

    // function that updates the Piece's vector of possible moves it can make,
    // given its location and surrounding pieces.
    void calculateMoves() override;
};

#endif
