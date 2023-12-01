#ifndef PIECE_H
#define PIECE_H
#include <memory>
#include <vector>
#include <iostream>
#include <string>
#include "square.h"
#include "move.h"

using namespace std;

class Board;

class Piece : public Observer{
    protected:
        enum Colour {WHITE, BLACK};
        bool hasMoved = false; 

        Colour pieceColour;
        Board* theBoard;
        char pieceName;
        Square* position;
        vector<Move> possibleMoves; // All legal moves
        vector<Move> blockedMoves; // All blocked moves

    public:
        virtual void calculateMoves() = 0;
        void movesInDir(Direction d);
        void notify(Square* s) override;
        void setColour(char c);
        int getX() { return position->getX(); }
        int getY() { return position->getY(); }
        char getPieceName() { return pieceName; }
        vector<Move> getMoves() { return possibleMoves; } 
        Colour getColour() { return pieceColour; }
        void pieceMoved() {hasMoved = true;}
};


#endif
 