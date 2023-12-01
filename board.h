#ifndef BOARD_H
#define BOARD_H

#include "square.h"
#include "piece.h"
#include "king.h"
#include "queen.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "pawn.h"

#include <vector>

using namespace std;

class Board {
    vector<vector<Square>> theBoard;
    vector<Piece*> availableWhites;
    vector<Piece*> availableBlacks;
    vector<Piece*> capturedWhites;
    vector<Piece*> capturedBlacks;

    int moveCounter;

public:
    bool containsBlackKing();
    bool containsWhiteKing();

    void incrMoveCounter();
    vector<vector<Square>> getBoard();
    vector<Piece*> getAvailableWhites() { return availableWhites; }
    vector<Piece*> getAvailableBlacks() { return availableBlacks; }
    void clearBoard();
    void initializeBoard();
    void setup();
};


#endif
