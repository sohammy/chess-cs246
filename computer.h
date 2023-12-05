#ifndef COMPUTER_H
#define COMPUTER_H
#include "player.h"
#include "move.h"
#include <vector>
#include "minimax.h"
#include "board.h"
using namespace std;

class Computer : public Player {
    Piece* attacker;
    Piece* defender;
    Square* startSquare;
    Square* destSquare;

    public:
        Computer();
        bool simulateMove(Board& gameBoard, Move m, Colour team);
        void undoMove(Board& gameBoard, Move m, Colour team);
        void makeMove(Board& gameBoard, Colour team);
        virtual Move doMove(Board& gameBoard, Colour team) = 0;
        int teamValueCalc(Move m, Colour initialTeam);
        Move generateMove(Board& gameBoard, Colour team, int levels, Colour initialTeam, int alpha, int beta);
        vector<Move> allMoves(Colour c, Board& gameBoard);
};


#endif
