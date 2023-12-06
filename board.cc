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
                    return 1;
                } else if (c == 'C') {
                    cout << "WHITE IS IN CHECK" << endl;
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
                    return 1;
                } else if (c == 'C') {
                    cout << "BLACK IS IN CHECK" << endl;
                    return 0;
                }
            }
        }
    }
    

    bool whiteCanMove = false;
    bool blackCanMove = false;
    if (team == 0) {
        for (unsigned int i = 0; i < availableWhites.size(); ++i) {
            if (availableWhites[i]->getMoves().size() != 0) {
                whiteCanMove = true;
            }
        }
        if (!whiteCanMove && !isMate()) {
            return 2;
        }
    } else if (team == 1) {
        for (unsigned int i = 0; i < availableBlacks.size(); ++i) {
            if (availableBlacks[i]->getMoves().size() != 0) {
                blackCanMove = true;
            }
        }
        if (!blackCanMove && !isMate()) {
            return 2;
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
    availableWhites.clear();
    availableBlacks.clear(); 
}

void Board::initializeBoard() {
    clearBoard();
    availableWhites.clear();
    availableBlacks.clear();
    theBoard.resize(BOARDSIZE); // Resizes the Board to be an 8x8 Grid
    for (int i = 0; i < BOARDSIZE; ++i) {
        theBoard[i].resize(BOARDSIZE);
    }

    for(int i = 0; i < BOARDSIZE; ++i) {
        for(int j = 0; j < BOARDSIZE; ++j) {
            theBoard[i][j].setX(i)->setY(j);
        }
    }

    vector<char> whiteChars = {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'};
    vector<char> blackChars = {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'};

    int index = 0;
    for(char c : whiteChars) {
        unique_ptr<Piece> p = nullptr;
        p = makePiece(c);
        availableWhites.push_back(move(p));
        if(index < BOARDSIZE) {
            theBoard[6][index].addPiece(availableWhites.back().get());
            theBoard[6][index].getPiece()->setColour('w');
            theBoard[6][index].getPiece()->setSquare(&theBoard[6][index]);
        } else {
            theBoard[7][index-BOARDSIZE].addPiece(availableWhites.back().get());
            theBoard[7][index-BOARDSIZE].getPiece()->setColour('w');
            theBoard[7][index-BOARDSIZE].getPiece()->setSquare(&theBoard[7][index-BOARDSIZE]);
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
        } else {
            theBoard[0][index-BOARDSIZE].addPiece(availableBlacks.back().get());
            theBoard[0][index-BOARDSIZE].getPiece()->setColour('b');
            theBoard[0][index-BOARDSIZE].getPiece()->setSquare(&theBoard[0][index-BOARDSIZE]);
        }
        ++index;
    }

    for(int i = 0; i < BOARDSIZE; ++i) {
       theBoard[0][i].getPiece()->calculateMoves(); 
       theBoard[1][i].getPiece()->calculateMoves();
       theBoard[6][i].getPiece()->calculateMoves();
       theBoard[7][i].getPiece()->calculateMoves();
    }
}

void Board::setup(bool& whoseTurn, TextDisplay* myTD) {
    cout << "You've Entered Setup Mode!" << endl;
    cout << endl;
    clearBoard();
    availableWhites.clear();
    availableBlacks.clear();
    whiteLose = false;
    blackLose = false;

    theBoard.resize(BOARDSIZE); // Resizes the Board to be an 8x8 Grid
    for (int i = 0; i < BOARDSIZE; ++i) {
        theBoard[i].resize(BOARDSIZE);
    }

    for(int i = 0; i < BOARDSIZE; ++i) {
        for(int j = 0; j < BOARDSIZE; ++j) {
            theBoard[i][j].setX(i)->setY(j);
        }
    }

    int boardSize = theBoard.size();
    for(int x = 0; x < boardSize; ++x) {
        for(int y = 0; y < boardSize; ++y) {
            theBoard[x][y].addDisplayObservers(myTD);
            theBoard[x][y].notifyDisplayObservers();
        }
    }

    string input;
    while (cin >> input) {

        for (unsigned int i = 0; i < input.length(); ++i) {
            input[i] = toupper(input[i]);
        }

        if (input == "DONE") {
            if (containsBlackKing() && containsWhiteKing()) {
                cout << "SETUP COMPLETE!" << endl;

                break;
            } else {
                cout << "YOU DO NOT HAVE 2 KINGS (BLACK AND WHITE) ON THE BOARD" << endl;
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

            if (piece == 'k' && containsBlackKing()) {
                cout << "ERROR: A BLACK KING ALREADY EXISTS ON THE BOARD!" << endl;
                continue;
            }

            if (piece == 'K' && containsWhiteKing()) {
                cout << "ERROR: A WHITE KING ALREADY EXISTS ON THE BOARD!" << endl;
                continue;
            }

            if (theBoard[placement.getInitX()][placement.getInitY()].getPiece() != nullptr) {
                removePiece(placement.getInitX(), placement.getInitY());
                theBoard[placement.getInitX()][placement.getInitY()].removePiece();
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

            if (isMate()) {
                removePiece(placement.getInitX(), placement.getInitY());
                theBoard[placement.getInitX()][placement.getInitY()].removePiece();
            }

            cout << *myTD << endl;

        } else if (input == "-") {
            string place;
            cin >> place;
            Move placement = Move(place, place, theBoard);
            int xCoord = placement.getInitX();
            int yCoord = placement.getInitY();

            if (theBoard[placement.getInitX()][placement.getInitY()].getPiece() == nullptr) {
                cout << "There is no piece on this square! Cannot perform operation!" << endl;
                continue;
            }

            char piece = theBoard[placement.getInitX()][placement.getInitY()].getPiece()->getPieceName();
            char isWhite  = false;

            if (65 <= piece && piece <= 90) {
                isWhite = true;
            }

            removePiece(xCoord, yCoord);
            theBoard[placement.getInitX()][placement.getInitY()].removePiece();

            if (isMate()) {
                
                unique_ptr<Piece> p = nullptr;
                p = makePiece(piece);
                cout << "Made Piece" << endl;

                if (isWhite) {
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
            }

            cout << *myTD << endl;
            
        } else if (input == "=WHITE" || input == "=white" ) {
            whoseTurn = 0;
        } else if (input == "=BLACK" || input == "=black" ) {
            whoseTurn = 1;
        } else if (input == "CLEAR") {
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

            int boardSize = theBoard.size();
            for(int x = 0; x < boardSize; ++x) {
                for(int y = 0; y < boardSize; ++y) {
                    theBoard[x][y].addDisplayObservers(myTD);
                    theBoard[x][y].notifyDisplayObservers();
                }
            }

            cout << *myTD << endl;
        } else if (input == "QUIT") {
            cout << "Thanks for Playing!" << endl;
            break;
        }
        
        else {
            cout << "Not a Valid Input!" << endl;
            continue;
        }
    }
}

bool Board::isMate() {
    for (unsigned int i = 0; i < theBoard.size(); ++i) {
        for (unsigned int j = 0; j < theBoard.size(); ++j) {
            if (dynamic_cast<King*>(theBoard[i][j].getPiece()) != nullptr) {
                    King* king = dynamic_cast<King*>(theBoard[i][j].getPiece());
                    char c = king->checkMate();
                    if (c == 'C') {
                        cout << "Your King is in Mate! Can't perform operation" << endl;
                        return true;
                    } else if (c == 'M') {
                        cout << "Your King is in Checkmate! Can't perform operation" << endl;
                        return true;
                    }
            }
        }
    }
    return false;
}

bool Board::isMate(Colour team) {
    for (unsigned int i = 0; i < theBoard.size(); ++i) {
        for (unsigned int j = 0; j < theBoard.size(); ++j) {
            if (dynamic_cast<King*>(theBoard[i][j].getPiece()) != nullptr) {
                if(theBoard[i][j].getPiece()->getColour() == team) {
                    King* king = dynamic_cast<King*>(theBoard[i][j].getPiece());
                    char c = king->checkMate();
                    if (c == 'C') {
                        return true;
                    } else if (c == 'M') {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void Board:: removePiece(int xCoord, int yCoord) {

    for (unsigned int i = 0; i < availableWhites.size(); ++i) {
        if (availableWhites[i]->getX() == xCoord && availableWhites[i]->getY() == yCoord) {
            availableWhites.erase(availableWhites.begin() + i);
        }
    }

    for (unsigned int i = 0; i < availableBlacks.size(); ++i) {
        if (availableBlacks[i]->getX() == xCoord && availableBlacks[i]->getY() == yCoord) {
            availableBlacks.erase(availableBlacks.begin() + i);
        }
    }

}

void Board::incrMoveCounter() {
    ++moveCounter;
}

vector<vector<Square>>& Board::getBoard() {
    return theBoard;
}
