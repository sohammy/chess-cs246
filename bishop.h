#ifndef __BISHOP_H__
#define __BISHOP_H__
#include <vector>
#include "square.h"
#include "piece.h"
using namespace std;

class Bishop: public Piece {

public:
    Bishop (vector<vector<Square>>& board);
    void calculateMoves();
};

#endif
