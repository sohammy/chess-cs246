#ifndef __BISHOP_H__
#define __BISHOP_H__
#include <vector>
#include "square.h"
#include "piece.h"
using namespace std;

// The Bishop class is a Piece, and represents the Bishop piece in the game

class Bishop: public Piece {

public:
    // Constructor
    Bishop (vector<vector<Square>>& board, char pieceType);

    //Function that updates the Piece's vector of possible moves it can make, given its location and surrounding pieces
    void calculateMoves() override;
};

#endif
