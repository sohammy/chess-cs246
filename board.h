#ifndef BOARD_H
#define BOARD_H

#include "square.h"

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

    void incrMoveCounter();

    void clearBoard();
    void initializeBoard();
    void setup();
};


#endif
