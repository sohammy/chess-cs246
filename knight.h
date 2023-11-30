#ifndef __KNIGHT_H__
#define __KNIGHT_H__
#include <vector>
#include "square.h"
using namespace std;

class Knight: public Piece {

private:
    void calculateMoves();
    bool canCastle();

};

#endif
