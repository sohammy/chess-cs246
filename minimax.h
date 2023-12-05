#ifndef MINIMAX_H
#define MINIMAX_H
#include "move.h"
#include "piece.h"
#include <vector>

Move maxOfMoves(vector<Move> moves);

Move minOfMoves(vector<Move> moves);

int getPieceValue(Piece* p);

#endif
