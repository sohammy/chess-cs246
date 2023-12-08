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
        vector<Move> getTeamsBlockedMoves(Colour c);

    public:
        
        Piece(vector<vector<Square>>& board, char pieceName);

        virtual void calculateMoves() = 0;
        
        // adds possible moves to vector in the direction given
        void movesInDir(Direction d, int n = 100);

        // notifies Square
        void notify(Square* s) override;

        // Sets Piece's colour to c
        void setColour(char c);

        // sets Piece's name
        void setPieceName(char c = ' ');

        // Sets the Square to s
        void setSquare(Square* s);

        // return Piece's name
        char getPieceName() { return pieceName; }

        // return x coordinate
        int getX() { return position->getX(); }

        // return y coordinate
        int getY() { return position->getY(); }

        // return a pointer to the Square the Piece is on
        Square* getSquare() {return position;}

        // return Vector of all possible moves
        vector<Move> getMoves() { return possibleMoves; }

        // return vector of blocked moves
        vector<Move> getBlockedMoves() { return blockedMoves; }

        // returns the Piece's Colour
        Colour getColour() { return pieceColour; }

        // sets Piece to reflect that it has moved its first turn
        void pieceMoved() { hasMoved = true; }

        // sets Piece to reflect that it has not taken its first turn
        void pieceUnMoved() { hasMoved = false; }

        // returns whether the Piece has ever moved or not
        bool hasItMoved() {return hasMoved;}

};

#endif
