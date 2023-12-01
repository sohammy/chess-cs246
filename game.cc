#include "game.h"

using namespace std;

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
    string whitePlayer;
    string blackPlayer;

    td = std::make_shared<TextDisplay>();

    cin >> whitePlayer >> blackPlayer;

    if (whitePlayer == "human") {
        white = make_unique<Human>();
    } else if (whitePlayer == "computer[1]") {
        white = make_unique<StageOne>();
    } else if (whitePlayer == "computer[2]") {
        white = make_unique<StageTwo>();
    } else if (whitePlayer == "computer[3]") {
        white = make_unique<StageThree>();
    } else if (whitePlayer == "computer[4]") {
        white = make_unique<StageFour>();
    } else {
        // ERROR MESSAGE //
    }

    if (blackPlayer == "human") {
        black = make_unique<Human>();
    } else if (blackPlayer == "computer[1]") {
        black = make_unique<StageOne>();
    } else if (blackPlayer == "computer[2]") {
        black = make_unique<StageTwo>();
    } else if (blackPlayer == "computer[3]") {
        black = make_unique<StageThree>();
    } else if (blackPlayer == "computer[4]") {
        black = make_unique<StageFour>();
    } else {
        // ERROR MESSAGE //
    }

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
            white->makeMove(myBoard); // getMove() should take in user input, only does move once 'move' is given as input (as per instructions)
            myBoard.incrMoveCounter();
        } if (whoseTurn) {
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
        myBoard.setup();
        play(myBoard);
    }
}
