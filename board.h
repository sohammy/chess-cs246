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

#include "textdisplay.h"

#include <vector>

using namespace std;

class Board {
    vector<vector<Square>> theBoard;
    vector<unique_ptr<Piece>> availableWhites;
    vector<unique_ptr<Piece>> availableBlacks;
    vector<unique_ptr<Piece>> capturedWhites;
    vector<unique_ptr<Piece>> capturedBlacks;

    int moveCounter;

public:
    bool containsBlackKing();
    bool containsWhiteKing();

    void incrMoveCounter();
    vector<vector<Square>>& getBoard();

    void clearBoard();
    void initializeBoard(TextDisplay *td);
    void setup();
};


#endif
