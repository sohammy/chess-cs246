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
    if (white.possibleMoves.size() == 0 && black.possibleMoves.size() == 1) { // possibleMoves is a Vector of ALL POSSIBLE MOVES where the King remains safe
        ++blackScore;
        return 1;
    } else if (white.possibleMoves.size() == 1 && black.possibleMoves.size() == 0) {
        ++whiteScore;
        return 0;
    }
    return -1;
}

void Game::play(Board& myBoard) {
    string whitePlayer;
    string blackPlayer;

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

    while (whoWon() == -1) { // Switches Turns Back and Forth between Black + White
        if (!whoseTurn) {
            white->getMove(); // getMove() should take in user input, only does move once 'move' is given as input (as per instructions)

        } if (whoseTurn) {
            black->getMove(); // getMove() should take in user input, only does move once 'move' is given as input (as per instructions)
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
