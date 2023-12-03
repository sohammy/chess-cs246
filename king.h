#ifndef KING_H
#define KING_H
#include "piece.h"
using namespace std;

// The King class is a Piece, and represents the King piece in the game

class King : public Piece {

    public:
    // Contructor:
    King (vector<vector<Square>>& board, char pieceType);

    // Vector of Moves the King can make (With exceptions)
    vector<Move> movesIncludingNonLegal(int x, int y);

    // function that updates the Piece's vector of possible moves it can make,
    // given its location and surrounding pieces.
    void calculateMoves() override;

    char checkMate();
};

#endif
