#include "game.h"

using namespace std;

// For Testing Purposes //

class Player {
    public:
        virtual void getMove() = 0;
};

class Human : public Player {
    public:
        void getMove() {
            cout << "Human Made Move" << endl;
        }
};

class StageOne : public Player {
    public:
        void getMove() {
            cout << "StageOne Made Move" << endl;
        }
};

class StageTwo : public Player {
    public:
        void getMove() {
            cout << "StageTwo Made Move" << endl;
        }
};

class StageThree : public Player {
    public:
        void getMove() {
            cout << "StageThree Made Move" << endl;
        }
};

class StageFour : public Player {
    public:
        void getMove() {
            cout << "StageFour Made Move" << endl;
        }
};

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ //

bool Game::hasWon() {
    // Checks if Either Player has Won
        // If White has No Valid Moves + Black Does -> White Loses
        // If Black has No Valid Moves + White Does -> Black Loses
        // Else Stalemate
    
    if (testCounter == 5) {
        return true;
    } 
    ++testCounter;
    cout << "Test Counter is at " << testCounter << endl;
    return false; 
}

void Game::play(string whitePlayer, string blackPlayer) { // Should play take in a board config???

    unique_ptr<Player> white;
    unique_ptr<Player> black;

    if (whitePlayer == "human") {
        white = make_unique<Human>();
    } else if (whitePlayer == "computer[1]") {
        white = make_unique<StageOne>();
    } else if (whitePlayer == "computer[2]") {
        white = make_unique<StageTwo>();
    } else if (whitePlayer == "computer[3]") {
        white = make_unique<StageThree>();
    } else if (blackPlayer == "computer[4]") {
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

    while (!hasWon()) { // Switches Turns Back and Forth between Black + White
        if (!whoseTurn) {
            white->getMove(); // getMove() should take in user input, only does move once 'move' is given as input (as per instructions)
        } if (whoseTurn) {
            black->getMove(); // getMove() should take in user input, only does move once 'move' is given as input (as per instructions)
        }
        whoseTurn = !whoseTurn;
    }
}