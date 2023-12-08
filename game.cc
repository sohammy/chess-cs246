#include "game.h"
#include "minimax.h"

using namespace std;


void playAgainMsg () {
    cout << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << " -- Type 'play' + [Player 1] + [Player 2] to Play Again!" << endl;
    cout << " -- Type 'setup' to enter Setup Mode!" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl;
}

void stringUpper (string& s) {
    for (unsigned int i = 0; i < s.length(); ++i) {
        s[i] = toupper(s[i]); 
    }
}

void Game::setTurn(char c) {
    if (c == 'b') {
        whoseTurn = 1;
    } else if (c == 'w') {
        whoseTurn = 0;
    } 
    return;
}

void Game::play(Board& myBoard) {
    gd = make_shared<GraphicsDisplay>(8); // GRAPHICS DISPLAY
    
    string whitePlayer;
    string blackPlayer;

    bool validWhite = false;
    bool validBlack = false;

    do {
        validWhite = false;
        validBlack = false;

        cin >> whitePlayer >> blackPlayer;

        stringUpper(whitePlayer);
        stringUpper(blackPlayer);

        if (whitePlayer == "HUMAN") {
            white = make_unique<Human>();
            validWhite = true;
        } else if (whitePlayer == "COMPUTER[1]") {
            white = make_unique<StageOne>();
            validWhite = true;
        } else if (whitePlayer == "COMPUTER[2]") {
            white = make_unique<StageTwo>();
            validWhite = true;
        } else if (whitePlayer == "COMPUTER[3]") {
            white = make_unique<StageThree>();
            validWhite = true;
        } else if (whitePlayer == "COMPUTER[4]") {
            white = make_unique<StageFour>();
            validWhite = true;
        } else if (whitePlayer == "COMPUTER[5]") {
            white = make_unique<StageFive>();
            validWhite = true;
        }

        if (blackPlayer == "HUMAN") {
            black = make_unique<Human>();
            validBlack = true;
        } else if (blackPlayer == "COMPUTER[1]") {
            black = make_unique<StageOne>();
            validBlack = true;
        } else if (blackPlayer == "COMPUTER[2]") {
            black = make_unique<StageTwo>();
            validBlack = true;
        } else if (blackPlayer == "COMPUTER[3]") {
            black = make_unique<StageThree>();
            validBlack = true;
        } else if (blackPlayer == "COMPUTER[4]") {
            black = make_unique<StageFour>();
            validBlack = true;
        } else if (blackPlayer == "COMPUTER[5]") {
            black = make_unique<StageFive>();
            validBlack = true;
        }

        if (!validWhite && !validBlack) {
            cout << "Not Valid Players! Please Enter 'human' or 'computer[x], 1 < x < 4" << endl;
        } if (!validWhite && validBlack) {
            cout << "Not a Valid White Player! Please Enter 'human' or 'computer[x], 1 <= x <= 4" << endl;
            cout << "You will have to reinput both Players Again." << endl;
        } if (!validBlack && validWhite) {
            cout << "Not a Valid Black Player! Please Enter 'human' or 'computer[x], 1 <= x <= 4" << endl;
            cout << "You will have to reinput both Players Again." << endl;
        }

    } while (!validWhite || !validBlack);

    cout << endl;
    cout << "Current Game: " << endl;
    cout << "Player #1 (WHITE): " << whitePlayer << endl;
    cout << "Player #2 (BLACK): " << blackPlayer << endl;
    cout << endl;

    int boardSize = myBoard.getBoard().size();
    for(int x = 0; x < boardSize; ++x) {
        for(int y = 0; y < boardSize; ++y) {
            myBoard.getBoard()[x][y].addDisplayObservers(td.get());
            myBoard.getBoard()[x][y].addDisplayObservers(gd.get()); // GRAPHICS DISPLAY
            myBoard.getBoard()[x][y].notifyDisplayObservers();
        }
    }

    while (myBoard.whoWon(whoseTurn) != 1 && myBoard.whoWon(whoseTurn) != 2 && !myBoard.whiteLose && !myBoard.blackLose) { // Switches Turns Back and Forth between Black + White
        cout << *td;
        if (!whoseTurn) {
            cout << "White's turn to move" << endl;
            white->makeMove(myBoard, WHITE); // getMove() should take in user input, only does move once 'move' is given as input (as per instructions)
            myBoard.incrMoveCounter();

            for (unsigned int i = 0; i < myBoard.getBoard().size(); ++i) {
                if (myBoard.getBoard()[0][i].getPiece() != nullptr) {
                    if (myBoard.getBoard()[0][i].getPiece()->getPieceName() == 'P') {
                        cout << "You can Promote your Pawn!" << endl;

                        myBoard.removePiece(0, i);
                        myBoard.getBoard()[0][i].removePiece();

                        cout << "INPUT A NEW PIECE: " << endl;

                        while(myBoard.getBoard()[0][i].getPiece() == nullptr) {
                            char newPiece;
                            if(whitePlayer != "HUMAN") {
                                newPiece = autoChoosePromotionPiece();
                            } else {
                                cin >> newPiece;
                            }
                            newPiece = toupper(newPiece);
                            if (newPiece == 'Q' || newPiece == 'R' || newPiece == 'B' || newPiece == 'N') {
                                unique_ptr<Piece> p = nullptr;
                                p = myBoard.makePiece(newPiece);
                                myBoard.availableWhites.push_back(move(p));
                                myBoard.getBoard()[0][i].addPiece(myBoard.availableWhites.back().get());
                                myBoard.getBoard()[0][i].getPiece()->setColour('w');
                                myBoard.getBoard()[0][i].getPiece()->setSquare(&myBoard.getBoard()[0][i]);
                                myBoard.getBoard()[0][i].getPiece()->calculateMoves();
                            } else {
                                cout << "Please input 'Q', 'R', 'B', or 'N'" << endl;
                            }
                        }
                    }
                }

                for (unsigned int i = 0; i < myBoard.getBoard()[2].size(); ++i) { // TURNS OFF ALL 'ENPASSANTABLE SQUARES' FOR BLACK
                    myBoard.getBoard()[2][i].turnOffEnPassant();
                }
            } 
            
        }

        else if (whoseTurn) {
            cout << "Black's turn to move" << endl;
            black->makeMove(myBoard, BLACK); // getMove() should take in user input, only does move once 'move' is given as input (as per instructions)
            myBoard.incrMoveCounter();

            for (unsigned int i = 0; i < myBoard.getBoard().size(); ++i) {
                if (myBoard.getBoard()[7][i].getPiece() != nullptr) {
                    if (myBoard.getBoard()[7][i].getPiece()->getPieceName() == 'p') {
                        cout << "You can Promote your Pawn!" << endl;

                        myBoard.removePiece(7, i);
                        myBoard.getBoard()[7][i].removePiece();

                        cout << "INPUT A NEW PIECE: " << endl;
                        
                        while(myBoard.getBoard()[7][i].getPiece() == nullptr) {
                            char newPiece;
                            if(blackPlayer != "HUMAN") {
                                newPiece = autoChoosePromotionPiece();
                            } else {
                                cin >> newPiece;
                            }
                            newPiece = tolower(newPiece);
                            if (newPiece == 'q' || newPiece == 'r' || newPiece == 'b' || newPiece == 'n') {
                                unique_ptr<Piece> p = nullptr;
                                p = myBoard.makePiece(newPiece);
                                myBoard.availableBlacks.push_back(move(p));
                                myBoard.getBoard()[7][i].addPiece(myBoard.availableBlacks.back().get());
                                myBoard.getBoard()[7][i].getPiece()->setColour('b');
                                myBoard.getBoard()[7][i].getPiece()->setSquare(&myBoard.getBoard()[7][i]);
                                myBoard.getBoard()[7][i].getPiece()->calculateMoves();
                            } else {
                                cout << "Please input 'Q', 'R', 'B', or 'N'" << endl;
                            }
                        }

                    }
                } 
            }

            for (unsigned int i = 0; i < myBoard.getBoard()[5].size(); ++i) { // TURNS OFF ALL 'ENPASSANTABLE SQUARES' FOR WHITE
                myBoard.getBoard()[5][i].turnOffEnPassant();
            }
        
        }
        if (whoseTurn == true) {
             whoseTurn = false;
        } else {
             whoseTurn = true;
        }  
    }

    if (myBoard.whoWon(whoseTurn) == 1) {
        if (whoseTurn == 0) {
            cout << "CHECKMATE! Black Wins!" << endl;

            playAgainMsg();

            ++blackScore;
            setTurn('w');
            gameStart();
        } else if (whoseTurn == 1) {
            cout << "CHECKMATE! White Wins!" << endl;

            playAgainMsg();
            
            ++whiteScore;
            setTurn('w');
            gameStart();
        }
    } else if (myBoard.whoWon(whoseTurn) == 2) {
            cout << "STALEMATE! Nobody Wins!" << endl;

            playAgainMsg();

            blackScore += 0.5;
            whiteScore += 0.5;
            setTurn('w');
            gameStart();
    }

    if (myBoard.whiteLose) {
        cout << "WHITE RESIGNED! Black Wins!" << endl;
        playAgainMsg();
        ++blackScore;
        setTurn('w');
        gameStart();
    } else if (myBoard.blackLose) {
        cout << "BLACK RESIGNED! White Wins!" << endl;
        playAgainMsg();
        ++whiteScore;
        setTurn('w');
        gameStart();
    }
}

void Game::gameStart() {
    cout << "-------------------------" << endl;
    cout << " Current White Score: " << whiteScore << endl;
    cout << " Current Black Score: " << blackScore << endl;
    cout << "-------------------------" << endl;
    cout << endl;
    
    Board myBoard;

    string input;
    cin >> input;

    if (input == "play") {
        myBoard.initializeBoard();
        play(myBoard);
    } else if (input == "setup") {
        myBoard.setup(whoseTurn, td.get());
        play(myBoard);
    } else if (input == "q" || input == "quit" || cin.eof()) {
        cout << "Thanks for Playing!" << endl;
        cout << "Final Score:" << endl;
        cout << "White Score: " << whiteScore << endl;
        cout << "Black Score: " << blackScore << endl;
    } else {
        cout << "Not a Valid Input" << endl;
    }
}

