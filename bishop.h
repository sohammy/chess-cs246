#ifndef BISHOP_H
#define BISHOP_H
#include "piece.h"
   
class Bishop : public Piece{
    public:
        void calculateMoves() override;
};

#endif
