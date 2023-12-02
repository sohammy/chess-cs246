#include "game.h"

using namespace std;

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


int Game::whoWon() {
    // if (white.checkMate()) { // Checks if White has been Checkmated
    //     ++blackScore;
    //     return 1;
    // } else if (black.checkMate()) { // Checks if Black has been Checkmated
    //     ++whiteScore;
    //     return 0;
    // } 
    // return -1;

    return -1;
}

void Game::play(Board& myBoard) {
    td = make_shared<TextDisplay>();
    
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
            myBoard.getBoard()[x][y].notifyDisplayObservers();
        }
    }

    while (whoWon() == -1) { // Switches Turns Back and Forth between Black + White
        cout << *td;
        if (!whoseTurn) {
            cout << "White's turn to move" << endl;
            white->makeMove(myBoard); // getMove() should take in user input, only does move once 'move' is given as input (as per instructions)
            myBoard.incrMoveCounter();
        } if (whoseTurn) {
            cout << "Black's turn to move" << endl;
            black->makeMove(myBoard); // getMove() should take in user input, only does move once 'move' is given as input (as per instructions)
            myBoard.incrMoveCounter();
        }
        whoseTurn = !whoseTurn;
    }
}

void Game::gameStart() {
    Board myBoard;

    string input;
    cin >> input;

    if (input == "play") {
        myBoard.initializeBoard();
        play(myBoard);
    } else if (input == "setup") {
        myBoard.setup(whoseTurn);
        play(myBoard);
    } else {
        cout << "Thanks for Playing!" << endl;
        cout << "White Score: " << whiteScore << endl;
        cout << "Black Score: " << blackScore << endl;
    }
}
