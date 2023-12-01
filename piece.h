#ifndef PIECE_H
#define PIECE_H

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

        bool hasMoved = false; 
        Colour pieceColour;
        vector<vector<Square>>& theBoard;
        char pieceName;
        Square* position;

        vector<Move> possibleMoves; // All legal moves
        vector<Move> blockedMoves; // All blocked moves
        
        vector<Piece*> getTeamOfColour(Colour c);
        vector<Move> getTeamsMoves(Colour c);

    public:
        
        Piece(vector<vector<Square>>& board);

        virtual void calculateMoves() = 0;
        
        void movesInDir(Direction d);
        void notify(Square* s) override;
        Piece* setColour(char c);
        Piece* setPieceName(char c = ' ');

        char getPieceName() { return pieceName; }
        int getX() { return position->getX(); }
        int getY() { return position->getY(); }
        vector<Move> getMoves() { return possibleMoves; }
        Colour getColour() { return pieceColour; }
        void pieceMoved() { hasMoved = true; }
};


#endif
 