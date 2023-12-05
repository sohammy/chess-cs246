#ifndef COMPUTER_H
#define COMPUTER_H
#include "player.h"
#include "move.h"
#include <vector>
#include "minimax.h"
#include "board.h"
using namespace std;

class Computer : public Player {
    Piece* attackPiece;
    char killedPiece;
    Square* startSquare;
    Square* killedPieceSquare;
    Square* attackPieceDest;

    public:
        Computer();
        void simulateMove(Board& gameBoard, Move m, Colour team);
        void undoMove(Board& gameBoard, Move m, Colour team);
        void makeMove(Board& gameBoard, Colour team);
        virtual Move doMove(Board& gameBoard, Colour team) = 0;
        int teamValueCalc(Board& gameBoard, Colour team);
        Move generateMove(Board& gameBoard, Colour team, int levels, Colour initialTeam);
        vector<Move> allMoves(Colour c, Board& gameBoard);
};


#endif
