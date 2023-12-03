#include "board.h"
#include <memory>
using namespace std;

const int BOARDSIZE = 8;

int Board::whoWon(bool team) {
    return -1;
}

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
    for (int i = 0; i < availableWhites.size(); ++i) {
        if (availableWhites[i]->getPieceName() == 'K') {
            return true;
        }
    }
    return false;
}

bool Board::containsBlackKing() {
    for (int i = 0; i < availableBlacks.size(); ++i) {
        if (availableBlacks[i]->getPieceName() == 'k') {
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

    vector<char> whiteChars = {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'R', 'N', 'B', 'K', 'Q', 'B', 'N', 'R'};
    vector<char> blackChars = {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'r', 'n', 'b', 'k', 'q', 'b', 'n', 'r'};

    int index = 0;
    for(char c : whiteChars) {
        unique_ptr<Piece> p = nullptr;
        p = makePiece(c, theBoard);
        availableWhites.push_back(move(p));
        if(index < BOARDSIZE) {
            theBoard[6][index].addPiece(availableWhites.back().get());
            theBoard[6][index].getPiece()->setColour('w');
            theBoard[6][index].getPiece()->setSquare(&theBoard[6][index]);
            theBoard[6][index].getPiece()->calculateMoves();
        } else {
            theBoard[7][index-BOARDSIZE].addPiece(availableWhites.back().get());
            theBoard[7][index-BOARDSIZE].getPiece()->setColour('w');
            theBoard[7][index-BOARDSIZE].getPiece()->setSquare(&theBoard[7][index-BOARDSIZE]);
            theBoard[7][index-BOARDSIZE].getPiece()->calculateMoves();
        }
        ++index;
    }

    index = 0;
    for(char c : blackChars) {
        unique_ptr<Piece> p = nullptr;
        p = makePiece(c, theBoard);
        availableBlacks.push_back(move(p));
        if(index < BOARDSIZE) {
            theBoard[1][index].addPiece(availableBlacks.back().get());
            theBoard[1][index].getPiece()->setColour('b');
            theBoard[1][index].getPiece()->setSquare(&theBoard[1][index]);
            theBoard[1][index].getPiece()->calculateMoves();
        } else {
            theBoard[0][index-BOARDSIZE].addPiece(availableBlacks.back().get());
            theBoard[0][index-BOARDSIZE].getPiece()->setColour('b');
            theBoard[0][index-BOARDSIZE].getPiece()->setSquare(&theBoard[0][index-BOARDSIZE]);
            theBoard[0][index-BOARDSIZE].getPiece()->calculateMoves();
        }
        ++index;
    }

}

void Board::setup(TextDisplay *td, bool& whoseTurn) {
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

        for (int i = 0; i < input.length(); ++i) {
            input[i] = toupper(input[i]);
        }

        if (input == "DONE") {
            if (containsBlackKing() && containsWhiteKing()) {
                cout << "You have met requirements" << endl;
                break;
            } else {
                cout << "You have not met requirements" << endl;
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

            if (theBoard[placement.getInitX()][placement.getInitY()].getPiece() != nullptr) {
                cout << "ERROR: A PIECE ALREADY EXISTS THERE" << endl;
                continue;
            }

            unique_ptr<Piece> p = nullptr;
            p = makePiece(piece, theBoard);
            
            if (white) {
                availableWhites.push_back(move(p));
                theBoard[placement.getInitX()][placement.getInitY()].addPiece(availableWhites.back().get());
                theBoard[placement.getInitX()][placement.getInitY()].getPiece()->setColour('w');
                theBoard[placement.getInitX()][placement.getInitY()].getPiece()->setSquare(&theBoard[placement.getInitX()][placement.getInitY()]);
                theBoard[placement.getInitX()][placement.getInitY()].getPiece()->calculateMoves();
            }
            else {
                availableBlacks.push_back(move(p));
                theBoard[placement.getInitX()][placement.getInitY()].addPiece(availableBlacks.back().get());
                theBoard[placement.getInitX()][placement.getInitY()].getPiece()->setColour('b');
                theBoard[placement.getInitX()][placement.getInitY()].getPiece()->setSquare(&theBoard[placement.getInitX()][placement.getInitY()]);
                theBoard[placement.getInitX()][placement.getInitY()].getPiece()->calculateMoves();
            }

            //cout << *td;

        } else if (input == "-") {
            string place;
            cin >> place;
            Move placement = Move(place, place, theBoard);
            int xCoord = placement.getInitX();
            int yCoord = placement.getInitY();

            for (unsigned int i = 0; i < availableWhites.size(); ++i) {
                if (availableWhites[i]->getX() == xCoord && availableWhites[i]->getY() == yCoord) {
                    availableWhites.erase(availableWhites.begin() + i);
                }
            }

            for (unsigned int i = 0; i < availableBlacks.size(); ++i) {
                if (availableBlacks[i]->getX() == xCoord && availableBlacks[i]->getY()) {
                    availableBlacks.erase(availableBlacks.begin() + i);
                }
            }

            theBoard[placement.getInitX()][placement.getInitY()].removePiece();

            //cout << *td; 
        } else if (input == "WHITE" ) {
            whoseTurn = 0;
        } else if (input == "BLACK") {
            whoseTurn = 1;
        }
    }
}

void Board::incrMoveCounter() {
    ++moveCounter;
}

vector<vector<Square>>& Board::getBoard() {
    return theBoard;
}
