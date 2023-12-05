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

    int moveCounter;

public:
    bool whiteLose;
    bool blackLose;
    vector<unique_ptr<Piece>> availableWhites;
    vector<unique_ptr<Piece>> availableBlacks;
    unique_ptr<Piece> makePiece (char pieceChar);

    bool isMate();

    bool containsBlackKing();
    bool containsWhiteKing();

    void incrMoveCounter();
    vector<vector<Square>>& getBoard();
    int whoWon(bool team);

    void clearBoard();
    void initializeBoard();
    void setup(bool& whoseTurn);

    void removePiece(int xCoord, int yCoord);
};

#endif
