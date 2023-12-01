#include "board.h"
#include <memory>
using namespace std;

const int BOARDSIZE = 8;

unique_ptr<Piece> makePiece (char pieceChar, vector<vector<Square>>& board) {
    char initChar = pieceChar;
    pieceChar = toupper(pieceChar);
    if (pieceChar == 'K') {
        return make_unique<King>(board, initChar);
    } else if (pieceChar == 'Q') {
        return make_unique<Queen>(board, initChar);
    } else if (pieceChar == 'R') {
        return make_unique<Rook>(board, initChar);
    } else if (pieceChar == 'B') {
        return make_unique<Bishop>(board, initChar);
    } else if (pieceChar == 'N') {
        return make_unique<Knight>(board, initChar);
    } else if (pieceChar == 'P') {
        return make_unique<Pawn>(board, initChar);
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

    unique_ptr<Rook> blackR1 = make_unique<Rook>(theBoard, 'r');
    unique_ptr<Rook> blackR2 = make_unique<Rook>(theBoard, 'r');
    unique_ptr<Bishop> blackB1 = make_unique<Bishop>(theBoard, 'b');
    unique_ptr<Bishop> blackB2 = make_unique<Bishop>(theBoard, 'b');
    unique_ptr<Knight> blackN1 = make_unique<Knight>(theBoard, 'n');
    unique_ptr<Knight> blackN2 = make_unique<Knight>(theBoard, 'n');
    unique_ptr<King> blackK1 = make_unique<King>(theBoard, 'k');
    unique_ptr<Queen> blackQ1 = make_unique<Queen>(theBoard, 'q');

    unique_ptr<Rook> whiteR1 = make_unique<Rook>(theBoard, 'R');
    unique_ptr<Rook> whiteR2 = make_unique<Rook>(theBoard, 'R');
    unique_ptr<Bishop> whiteB1 = make_unique<Bishop>(theBoard, 'B');
    unique_ptr<Bishop> whiteB2 = make_unique<Bishop>(theBoard, 'B');
    unique_ptr<Knight> whiteN1 = make_unique<Knight>(theBoard, 'N');
    unique_ptr<Knight> whiteN2 = make_unique<Knight>(theBoard, 'N');
    unique_ptr<King> whiteK1 = make_unique<King>(theBoard, 'K');
    unique_ptr<Queen> whiteQ1 = make_unique<Queen>(theBoard, 'Q');

    theBoard[0][0].addPiece (blackR1.get());
    theBoard[0][1].addPiece (blackN1.get());
    theBoard[0][2].addPiece (blackB1.get());
    theBoard[0][3].addPiece (blackQ1.get());
    theBoard[0][4].addPiece (blackK1.get());
    theBoard[0][5].addPiece (blackB2.get());
    theBoard[0][6].addPiece (blackN2.get());
    theBoard[0][7].addPiece (blackR2.get());

    for (int i = 0; i < BOARDSIZE; ++i) {
        theBoard[0][i].getPiece()->setColour('b');
    }

    theBoard[7][0].addPiece (whiteR1.get());
    theBoard[7][1].addPiece (whiteN1.get());
    theBoard[7][2].addPiece (whiteB1.get());
    theBoard[7][3].addPiece (whiteQ1.get());
    theBoard[7][4].addPiece (whiteK1.get());
    theBoard[7][5].addPiece (whiteB2.get());
    theBoard[7][6].addPiece (whiteN2.get());
    theBoard[7][7].addPiece (whiteR2.get());

    for (int i = 0; i < BOARDSIZE; ++i) {
        theBoard[7][i].getPiece()->setColour('w');
    }

    for (int i = 0; i < BOARDSIZE; ++i) {
        // theBoard[1][i].addPiece(make_unique<Pawn>(theBoard, 'p').get());
        // theBoard[1][i].getPiece()->setColour('b');
        // theBoard[6][i].addPiece(make_unique<Pawn>(theBoard, 'P').get());
        // theBoard[6][i].getPiece()->setColour('w');
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
                theBoard[placement.getInitX()][placement.getInitY()].getPiece()->setColour('w');
            } else {
                theBoard[placement.getInitX()][placement.getInitY()].getPiece()->setColour('b');
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
