#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Knight : public Piece {
    public:
        Knight (vector<vector<Square>>& board);
        void calculateMoves();
};


#endif
