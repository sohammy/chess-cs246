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

    // Makes a Unique Pointer to the Piece corresponding to pieceChar
    unique_ptr<Piece> makePiece (char pieceChar);

    // Checks if there are ANY CHECKMATES/CHECKS on the Board
    bool isMate();

    // Checks if Team of Colour has ANY CHECKMATES/CHECKS on the Board
    bool isMate(Colour team);

    // Checks if the Board contains a BLACK KING
    bool containsBlackKing();

    // Checks if the Board contains a WHITE KING
    bool containsWhiteKing();

    // Increments Move Counter every time a MOVE IS MADE
    void incrMoveCounter();

    // Returns a Reference to the GAME BOARD
    vector<vector<Square>>& getBoard();

    // Determines whether the team is in CHECK/CHECKMATE/STALEMATE, returns an int corresponding to each
    int whoWon(bool team);

    // Clears the Board, and all Unique Ptrs to Pieces
    void clearBoard();

    // Initializaes Board to have the 'typical' Chess Layout
    void initializeBoard();

    // Allows User to SETUP the Board however they like -- Requires them to follow BASIC GUIDELINES of Chess
    void setup(bool& whoseTurn, TextDisplay* myTD);

    // Removes the Piece at the Square, xCoord, yCoord
    void removePiece(int xCoord, int yCoord);
};

#endif
