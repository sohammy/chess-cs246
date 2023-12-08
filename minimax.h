#ifndef MINIMAX_H
#define MINIMAX_H
#include "move.h"
#include "piece.h"
#include <vector>

// Returns the Move with the MAXIMUM VALUE determined by PRE-DETERMINED Piece Values
Move maxOfMoves(vector<Move> moves);

// Returns the Move with the MINIMUM VALUE determined by PRE-DETERMINED Piece Values
Move minOfMoves(vector<Move> moves);

// Returns the Pre-Determined Value for Piece, p
int getPieceValue(Piece* p);

char autoChoosePromotionPiece();

#endif
