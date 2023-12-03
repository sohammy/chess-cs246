#include "board.h"
#include <memory>
using namespace std;

const int BOARDSIZE = 8;

int Board::whoWon(bool team) {
    if(!team) {
        for(unsigned int i = 0; i < availableWhites.size(); ++i) {
            Piece* p = availableWhites[i].get();
            if(dynamic_cast<King*>(p) != nullptr) {
                King* king = dynamic_cast<King*>(p);
                char c = king->checkMate();
                if (c == 'M') {
                    cout << "CHECKMATE WHITE" << endl;
                    return 1;
                } else if (c == 'C') {
                    cout << "IN CHECK WHITE" << endl;
                    return 0;
                }
            }
        }
    } else if (team) {
        for(unsigned int i = 0; i < availableBlacks.size(); ++i) {
            Piece* p = availableBlacks[i].get();
            if(dynamic_cast<King*>(p) != nullptr) {
                King* king = dynamic_cast<King*>(p);
                char c = king->checkMate();
                if (c == 'M') {
                    cout << "CHECKMATE BLACK" << endl;
                    return 1;
                } else if (c == 'C') {
                    cout << "IN CHECK BLACK" << endl;
                    return 0;
                }
            }
        }
    }
    return -1;
}

unique_ptr<Piece> Board::makePiece (char pieceChar) {
    char initChar = pieceChar;
    pieceChar = toupper(pieceChar);
    if (pieceChar == 'K') {
        return make_unique<King>(theBoard, initChar);
    } else if (pieceChar == 'Q') {
        return make_unique<Queen>(theBoard, initChar);
    } else if (pieceChar == 'R') {
        return make_unique<Rook>(theBoard, initChar);
    } else if (pieceChar == 'B') {
        return make_unique<Bishop>(theBoard, initChar);
    } else if (pieceChar == 'N') {
        return make_unique<Knight>(theBoard, initChar);
    } else if (pieceChar == 'P') {
        return make_unique<Pawn>(theBoard, initChar);
    }
    return nullptr;
}


bool Board::containsWhiteKing() {
    for (unsigned int i = 0; i < availableWhites.size(); ++i) {
        if (availableWhites[i]->getPieceName() == 'K') {
            return true;
        }
    }
    return false;
}

bool Board::containsBlackKing() {
    for (unsigned int i = 0; i < availableBlacks.size(); ++i) {
        if (availableBlacks[i]->getPieceName() == 'k') {
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
        p = makePiece(c);
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
        p = makePiece(c);
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

void Board::setup(bool& whoseTurn) {
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

        for (unsigned int i = 0; i < input.length(); ++i) {
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

            // Checking for Errors
            if (theBoard[placement.getInitX()][placement.getInitY()].getPiece() != nullptr) {
                cout << "ERROR: A PIECE ALREADY EXISTS THERE" << endl;
                continue;
            }

            if ((piece == 'P') && (placement.getDestX() == 7)) {
                cout << "ERROR: CANNOT PLACE WHITE PAWN in ROW #1" << endl;
                continue;
            }

            if ((piece == 'p') && (placement.getDestX() == 0)) {
                cout << "ERROR: CANNOT PLACE BLACK PAWN in ROW #8" << endl;
                continue;
            }

            unique_ptr<Piece> p = nullptr;
            p = makePiece(piece);
            cout << "Made Piece" << endl;
            
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

            if (dynamic_cast<King*>(theBoard[placement.getInitX()][placement.getInitY()].getPiece()) != nullptr) {
                    cout << "Here" << endl;
                    King* king = dynamic_cast<King*>(theBoard[placement.getInitX()][placement.getInitY()].getPiece());
                    char c = king->checkMate();
                    cout << "char is " << c << endl;
                    if (c == 'M') {
                        cout << "Your King is in Mate! Can't Be Placed Here!" << endl;
                        removePiece(placement.getInitX(), placement.getInitY());
                    } else if (c == 'C') {
                        cout << "Your King is in Checkmate! Can't Be Placed Here!" << endl;
                        removePiece(placement.getInitX(), placement.getInitY());
                    }
            }

        } else if (input == "-") {
            string place;
            cin >> place;
            Move placement = Move(place, place, theBoard);
            int xCoord = placement.getInitX();
            int yCoord = placement.getInitY();

            removePiece(xCoord, yCoord);

            theBoard[placement.getInitX()][placement.getInitY()].removePiece();
            
        } else if (input == "WHITE" ) {
            whoseTurn = 0;
        } else if (input == "BLACK") {
            whoseTurn = 1;
        }
    }
}

void Board:: removePiece(int xCoord, int yCoord) {
    //cout << "White Before has " << availableWhites.size() << " Pieces" << endl;
    //cout << "Black Before Has " << availableBlacks.size() << " Pieces" << endl;

    for (unsigned int i = 0; i < availableWhites.size(); ++i) {
        //cout << "Looking at White" << endl;
        if (availableWhites[i]->getX() == xCoord && availableWhites[i]->getY() == yCoord) {
            availableWhites.erase(availableWhites.begin() + i);
        }
    }

    for (unsigned int i = 0; i < availableBlacks.size(); ++i) {
        //cout << "Looking at Black" << endl;
        if (availableBlacks[i]->getX() == xCoord && availableBlacks[i]->getY() == yCoord) {
            availableBlacks.erase(availableBlacks.begin() + i);
        }
    }

    //cout << "White Now has " << availableWhites.size() << " Pieces" << endl;
    //cout << "Black Now Has " << availableBlacks.size() << " Pieces" << endl;
}

void Board::incrMoveCounter() {
    ++moveCounter;
}

vector<vector<Square>>& Board::getBoard() {
    return theBoard;
}
