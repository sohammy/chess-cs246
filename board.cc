#include "board.h"
#include <memory>
using namespace std;

const int BOARDSIZE = 8;

unique_ptr<Piece> makePiece (char pieceChar, vector<vector<Square>>& board) {
    pieceChar = toupper(pieceChar);
    if (pieceChar == 'K') {
        return make_unique<King>(board);
    } else if (pieceChar == 'Q') {
        return make_unique<Queen>(board);
    } else if (pieceChar == 'R') {
        return make_unique<Rook>(board);
    } else if (pieceChar == 'B') {
        return make_unique<Bishop>(board);
    } else if (pieceChar == 'N') {
        return make_unique<Knight>(board);
    } else if (pieceChar == 'P') {
        return make_unique<Pawn>(board);
    }
    return nullptr;
}


bool Board::containsWhiteKing() {
    for (Piece* p : availableWhites) {
        if (dynamic_cast<King*>(p) != nullptr) {
            return true;
        }
    }
    return false;
}

bool Board::containsBlackKing() {
    for (Piece* p : availableBlacks) {
        if (dynamic_cast<King*>(p) != nullptr) {
            return true;
        }
    }
    return false;
}

void Board::clearBoard() {
    theBoard.clear();
}

void Board::initializeBoard(TextDisplay *td) {
    clearBoard();
    theBoard.resize(BOARDSIZE); // Resizes the Board to be an 8x8 Grid
    for (int i = 0; i < BOARDSIZE; ++i) {
        theBoard[i].resize(BOARDSIZE);
    }

    for(int i = 0; i < BOARDSIZE; ++i) {
        for(int j = 0; j < BOARDSIZE; ++j) {
            theBoard[i][j].setX(i)->setY(j);
        }
    }

    theBoard[0][0].addPiece (make_unique<Rook>(theBoard).get()->setPieceName('R'));
    theBoard[0][1].addPiece (make_unique<Knight>(theBoard).get()->setPieceName('N'));
    theBoard[0][2].addPiece (make_unique<Bishop>(theBoard).get()->setPieceName('B'));
    theBoard[0][3].addPiece (make_unique<Queen>(theBoard).get()->setPieceName('Q'));
    theBoard[0][4].addPiece (make_unique<King>(theBoard).get()->setPieceName('K'));
    theBoard[0][5].addPiece (make_unique<Bishop>(theBoard).get()->setPieceName('B'));
    theBoard[0][6].addPiece (make_unique<Knight>(theBoard).get()->setPieceName('N'));
    theBoard[0][7].addPiece (make_unique<Rook>(theBoard).get()->setPieceName('R'));

    for (int i = 0; i < BOARDSIZE; ++i) {
        theBoard[0][i].getPiece()->setColour('b');
    }

    theBoard[7][0].addPiece (make_unique<Rook>(theBoard).get()->setPieceName('r'));
    theBoard[7][1].addPiece (make_unique<Knight>(theBoard).get()->setPieceName('k'));
    theBoard[7][2].addPiece (make_unique<Bishop>(theBoard).get()->setPieceName('b'));
    theBoard[7][3].addPiece (make_unique<Queen>(theBoard).get()->setPieceName('q'));
    theBoard[7][4].addPiece (make_unique<King>(theBoard).get()->setPieceName('k'));
    theBoard[7][5].addPiece (make_unique<Bishop>(theBoard).get()->setPieceName('b'));
    theBoard[7][6].addPiece (make_unique<Knight>(theBoard).get()->setPieceName('n'));
    theBoard[7][7].addPiece (make_unique<Rook>(theBoard).get()->setPieceName('r'));

    for (int i = 0; i < BOARDSIZE; ++i) {
        theBoard[7][i].getPiece()->setColour('w');
    }

    for (int i = 0; i < BOARDSIZE; ++i) {
        theBoard[1][i].addPiece(make_unique<Pawn>(theBoard).get());
        theBoard[1][i].getPiece()->setColour('b')->setPieceName('p');
        theBoard[6][i].addPiece(make_unique<Pawn>(theBoard).get());
        theBoard[6][i].getPiece()->setColour('w')->setPieceName('P');
    }

}

void Board::setup() {
    clearBoard();

    theBoard.resize(BOARDSIZE); // Resizes the Board to be an 8x8 Grid
    for (int i = 0; i < BOARDSIZE; ++i) {
        theBoard[i].resize(BOARDSIZE);
    }

    for(int i = 0; i < BOARDSIZE; ++i) {
        for(int j = 0; j < BOARDSIZE; ++j) {
            theBoard[i][j].setX(i)->setY(j);
        }
    }

    string input;
    while (cin >> input) {
        if (input == "done") {
            if (containsBlackKing() && containsWhiteKing()) {
                break;
            }
        } else if (input == "+") {
            char piece;
            string place;
            cin >> piece >> place;
            Move placement = Move(place, place, theBoard);

            bool white = false;
            if (65 <= piece && piece <= 90) {
                white = true;
            }

            theBoard[placement.getInitX()][placement.getInitY()].addPiece(makePiece(piece, theBoard).get());
            
            if (white) {
                theBoard[placement.getInitX()][placement.getInitY()].getPiece()->setColour('w')->setPieceName(piece);
            } else {
                theBoard[placement.getInitX()][placement.getInitY()].getPiece()->setColour('b')->setPieceName(piece);
            }

        } else if (input == "-") {
            string place;
            cin >> place;
            Move placement = Move(place, place, theBoard);
            theBoard[placement.getInitX()][placement.getInitY()].removePiece();
        }
    }
}

void Board::incrMoveCounter() {
    ++moveCounter;
}

vector<vector<Square>>& Board::getBoard() {
    return theBoard;
}
