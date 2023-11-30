#ifndef __BISHOP_H__
#define __BISHOP_H__
#include <vector>
#include "square.h"
using namespace std;

class Bishop: public Piece {

public:
    void calculateMoves();
    
};

#endif
