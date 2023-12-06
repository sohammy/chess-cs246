#ifndef COMPUTER_H
#define COMPUTER_H
#include "player.h"
#include "move.h"
#include <vector>
#include "minimax.h"
#include "board.h"
using namespace std;

const int INTREALLYHIGH = 10000000;
const int INTREALLLOW = -10000000;

class Computer : public Player {
    Piece* attacker;
    Piece* defender;
    Square* startSquare;
    Square* destSquare;

    public:
        // Constructor
        Computer();

        // simulateMove(Board, Move, Colour) makes a move behind the scenes and is used to 
        // determine the quality of a move, if this function returns false, then we shouldn't
        // generate a tree starting from this move
        bool simulateMove(Board& gameBoard, Move m, Colour team);

        // undoMove(Board, Move, Colour) is used to reset the board back to it's initial state, assuming
        // that simulate moves was successful
        void undoMove(Board& gameBoard, Move m, Colour team);

        // generateMove(Board, Colour, int, Colour) is a recursive function that implements the minimax algorithm
        // in order to find the best move for a computer player
        void makeMove(Board& gameBoard, Colour team);

    
        virtual Move doMove(Board& gameBoard, Colour team) = 0;
        int teamValueCalc(Move m, Colour initialTeam);
        Move generateMove(Board& gameBoard, Colour team, int levels, Colour initialTeam, int alpha, int beta);
        vector<Move> allMoves(Colour c, Board& gameBoard);
};


#endif
