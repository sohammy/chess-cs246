#ifndef BOARD_H
#define BOARD_H

#include "square.h"
#include "piece.h"
#include "king.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"
#include "pawn.h"

#include <vector>

using namespace std;

class Board {
    vector<vector<shared_ptr<Square>>> theBoard;
    vector<Piece*> availableWhites;
    vector<Piece*> availableBlacks;
    vector<Piece*> capturedWhites;
    vector<Piece*> capturedBlacks;

    int moveCounter;

public:
    bool containsBlackKing();
    bool containsWhiteKing();

    void incrMoveCounter();
    vector<vector<shared_ptr<Square>>> getBoard();

    void clearBoard();
    void initializeBoard();
    void setup();
};


#endif
