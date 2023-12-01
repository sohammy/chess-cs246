#ifndef BOARD_H
#define BOARD_H

#include "square.h"
#include "piece.h"

#include <vector>

using namespace std;


class Board {
    vector<vector<unique_ptr<Square>>> theBoard;
    vector<Piece*> availableWhites;
    vector<Piece*> availableBlacks;
    vector<Piece*> capturedWhites;
    vector<Piece*> capturedBlacks;

    int moveCounter;

public:
    bool containsBlackKing();
    bool containsWhiteKing();

    vector<Piece*> availableWhites() { return availableWhites; }
    vector<Piece*> availableBlacks() { return availableBlacks; }

    void incrMoveCounter();

    void clearBoard();
    void initializeBoard();
    void setup();
};


#endif
