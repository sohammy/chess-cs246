#include "board.h"

bool Board::containsWhiteKing() {
    for (Piece p : availableWhites) {
        if (King* king = dynamic_cast<King*>(p)) {
            return true;
        }
    }
    return false;
}

bool Board::containsBlackKing() {
    for (Piece p : availableBlacks) {
        if (King* king = dynamic_cast<King*>(p)) {
            return true;
        }
    }
    return false;
}

void Board::clearBoard() {
    theBoard.clear();
}

void Board::initializeBoard() {
    clearBoard();
    int boardSize = 8;

    theBoard.resize(boardSize); // Resizes the Board to be an 8x8 Grid
    for (int i = 0; i < boardSize; ++i) {
        theBoard[i].resize(boardSize);
    }

    theBoard[0][0]->curpiece = make_unique<Rook>();
    theBoard[0][1]->curpiece = make_unique<Knight>();
    theBoard[0][2]->curpiece = make_unique<Bishop>();
    theBoard[0][3]->curpiece = make_unique<Queen>();
    theBoard[0][4]->curpiece = make_unique<King>();
    theBoard[0][5]->curpiece = make_unique<Bishop>();
    theBoard[0][6]->curpiece = make_unique<Knight>();
    theBoard[0][7]->curpiece = make_unique<Rook>();

    for (int i = 0; i < boardSize; ++i) {
        theBoard[0][i]->curpiece.setColour('b')
    }

    theBoard[7][0]->curpiece = make_unique<Rook>();
    theBoard[7][1]->curpiece = make_unique<Knight>();
    theBoard[7][2]->curpiece = make_unique<Bishop>();
    theBoard[7][3]->curpiece = make_unique<Queen>();
    theBoard[7][4]->curpiece = make_unique<King>();
    theBoard[7][5]->curpiece = make_unique<Bishop>();
    theBoard[7][6]->curpiece = make_unique<Knight>();
    theBoard[7][7]->curpiece = make_unique<Rook>();

    for (int i = 0; i < boardSize; ++i) {
        theBoard[7][i]->curpiece.setColour('w');
    }

    for (int i = 0; i < 7; ++i) {
        theBoard[1][i]->curpiece = make_unique<Pawn>();
        theBoard[1][i]->curpiece.setColour('b');
        theBoard[6][i]->curpiece = make_unique<Pawn>()
        theBoard[6][i]->curpiece.setColour('w');
    }


}

void Board::setup() {
    clearBoard();
    int boardSize = 8;

    theBoard.resize(boardSize); // Resizes the Board to be an 8x8 Grid
    for (int i = 0; i < boardSize; ++i) {
        theBoard[i].resize(boardSize);
    }

    string input;
    while (cin >> input) {
        if (input == "done") {
            if (containsBlackKing() && containsWhiteKing()) {
                break;
            }
        } else if (input == "+") {
            string piece, place;
            cin >> piece >> place;
            Move placement = Move(place, place);
            theBoard[placement.getInitX()][placement.getInitY()].addPiece(piece);
        } else if (input == "-") {
            string place;
            cin >> place;
            Move placement = Move(place, place);
            theBoard[placement.getInitX()][placement.getInitY()].removePiece();
        }
    }
}

void Board::incrMoveCounter() {
    ++moveCounter;
}