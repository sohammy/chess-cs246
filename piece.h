#ifndef PIECE_H
#define PIECE_H__
#include <memory>
#include <vector>
#include <iostream>
#include <string>
#include "square.h"
#include "move.h"
using namespace std;

class Piece : public Observer{
    protected:
        enum Colour {WHITE, BLACK};

        Colour pieceColour;
        char pieceName;
        Square* position;
        vector<Move> possibleMoves; // All legal moves
        vector<Move> blockedMoves; // All blocked moves

    public:
        virtual void calculateMoves() = 0;
        void movesInDir(Direction d);
        void notify(Square& s) override;
        void setColour(char c);
        int getX() { return position->getX(); }
        int getY() { return position->getY(); }
        vector<Move> getMoves() { return possibleMoves; } 
        Colour getColour() { return pieceColour; }

};


#endif
 