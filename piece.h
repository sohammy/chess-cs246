#ifndef PIECE_H
#define PIECE_H

#include <memory>
#include <vector>
#include <iostream>
#include <string>
#include "square.h"
#include "move.h"

using namespace std;

enum Colour {WHITE, BLACK};

class Piece : public Observer{
    protected:

        bool hasMoved = false; // Accessed within player through pieceMoved()

        Colour pieceColour;
        vector<vector<Square>>& theBoard;
        char pieceName;
        Square* position;

        vector<Move> possibleMoves; // All legal moves
        vector<Move> blockedMoves; // All blocked moves
        
        vector<Piece*> getTeamOfColour(Colour c);
        vector<Move> getTeamsMoves(Colour c);

    public:
        
        Piece(vector<vector<Square>>& board, char pieceName);

        virtual void calculateMoves() = 0;
        
        void movesInDir(Direction d);
        void notify(Square* s) override;
        void setColour(char c);
        void setPieceName(char c = ' ');
        void setSquare(Square* s);

        char getPieceName() { return pieceName; }
        int getX() { return position->getX(); }
        int getY() { return position->getY(); }
        vector<Move> getMoves() { return possibleMoves; }
        Colour getColour() { return pieceColour; }
        void pieceMoved() { hasMoved = true; }

};


#endif
 