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
    unique_ptr<Rook> blackB1 = make_unique<Rook>(theBoard, 'b');
    unique_ptr<Rook> blackB2 = make_unique<Rook>(theBoard, 'b');
    unique_ptr<Rook> blackN1 = make_unique<Rook>(theBoard, 'n');
    unique_ptr<Rook> blackN2 = make_unique<Rook>(theBoard, 'n');
    unique_ptr<Rook> blackK1 = make_unique<Rook>(theBoard, 'k');
    unique_ptr<Rook> blackQ1 = make_unique<Rook>(theBoard, 'q');

    unique_ptr<Rook> whiteR1 = make_unique<Rook>(theBoard, 'R');
    unique_ptr<Rook> whiteR2 = make_unique<Rook>(theBoard, 'R');
    unique_ptr<Rook> whiteB1 = make_unique<Rook>(theBoard, 'B');
    unique_ptr<Rook> whiteB2 = make_unique<Rook>(theBoard, 'B');
    unique_ptr<Rook> whiteN1 = make_unique<Rook>(theBoard, 'N');
    unique_ptr<Rook> whiteN2 = make_unique<Rook>(theBoard, 'N');
    unique_ptr<Rook> whiteK1 = make_unique<Rook>(theBoard, 'K');
    unique_ptr<Rook> whiteQ1 = make_unique<Rook>(theBoard, 'Q');

    theBoard[0][0].addPiece (blackR1.get());
    theBoard[0][1].addPiece (blackN1.get());
    theBoard[0][2].addPiece (blackB1.get());
    theBoard[0][3].addPiece (blackQ1.get());
    theBoard[0][4].addPiece (blackK1.get());
    theBoard[0][5].addPiece (blackB2.get());
    theBoard[0][6].addPiece (blackN2.get());
    theBoard[0][7].addPiece (blackR2.get());

    theBoard[7][0].addPiece (whiteR1.get());
    theBoard[7][1].addPiece (whiteN1.get());
    theBoard[7][2].addPiece (whiteB1.get());
    theBoard[7][3].addPiece (whiteQ1.get());
    theBoard[7][4].addPiece (whiteK1.get());
    theBoard[7][5].addPiece (whiteB2.get());
    theBoard[7][6].addPiece (whiteN2.get());
    theBoard[7][7].addPiece (whiteR2.get());

    unique_ptr<Pawn> whiteP1 = make_unique<Pawn>(theBoard, 'P');
    unique_ptr<Pawn> whiteP2 = make_unique<Pawn>(theBoard, 'P');
    unique_ptr<Pawn> whiteP3 = make_unique<Pawn>(theBoard, 'P');
    unique_ptr<Pawn> whiteP4 = make_unique<Pawn>(theBoard, 'P');
    unique_ptr<Pawn> whiteP5 = make_unique<Pawn>(theBoard, 'P');
    unique_ptr<Pawn> whiteP6 = make_unique<Pawn>(theBoard, 'P');
    unique_ptr<Pawn> whiteP7 = make_unique<Pawn>(theBoard, 'P');
    unique_ptr<Pawn> whiteP8 = make_unique<Pawn>(theBoard, 'P');
    unique_ptr<Pawn> blackP1 = make_unique<Pawn>(theBoard, 'p');
    unique_ptr<Pawn> blackP2 = make_unique<Pawn>(theBoard, 'p');
    unique_ptr<Pawn> blackP3 = make_unique<Pawn>(theBoard, 'p');
    unique_ptr<Pawn> blackP4 = make_unique<Pawn>(theBoard, 'p');
    unique_ptr<Pawn> blackP5 = make_unique<Pawn>(theBoard, 'p');
    unique_ptr<Pawn> blackP6 = make_unique<Pawn>(theBoard, 'p');
    unique_ptr<Pawn> blackP7 = make_unique<Pawn>(theBoard, 'p');
    unique_ptr<Pawn> blackP8 = make_unique<Pawn>(theBoard, 'p');

   theBoard[1][0].addPiece(whiteP1.get());
   theBoard[1][1].addPiece(whiteP2.get()); 
   theBoard[1][2].addPiece(whiteP3.get()); 
   theBoard[1][3].addPiece(whiteP4.get());  
   theBoard[1][4].addPiece(whiteP5.get()); 
   theBoard[1][5].addPiece(whiteP6.get()); 
   theBoard[1][6].addPiece(whiteP7.get()); 
   theBoard[1][7].addPiece(whiteP8.get());

   theBoard[6][0].addPiece(blackP1.get());
   theBoard[6][1].addPiece(blackP2.get());
   theBoard[6][2].addPiece(blackP3.get());
   theBoard[6][3].addPiece(blackP4.get()); 
   theBoard[6][4].addPiece(blackP5.get());
   theBoard[6][5].addPiece(blackP6.get());
   theBoard[6][6].addPiece(blackP7.get());
   theBoard[6][7].addPiece(blackP8.get());

    for (int i = 0; i < BOARDSIZE; ++i) {
        theBoard[1][i].getPiece()->setColour('b');
        theBoard[6][i].getPiece()->setColour('w');
        theBoard[7][i].getPiece()->setColour('w');
        theBoard[0][i].getPiece()->setColour('b');
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
