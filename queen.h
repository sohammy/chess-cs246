#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class Queen : public Piece {

public:
    Queen (vector<vector<Square>>& board, char pieceType);
    void calculateMoves() override;
};

#endif
