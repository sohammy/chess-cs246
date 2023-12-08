#ifndef MOVE_H
#define MOVE_H
#include <string>
#include "square.h"
using namespace std;


enum Direction{N, E, S, W, NE, SE, SW, NW, NONE};

class Move {
    int initialX;
    int initialY;
    int destinationX;
    int destinationY;
    int moveValue;
    Square* destSquare;
    Direction moveDirection;

    int letterToInt(char c);
    Direction coordsToDirection(int x, int y, int nextX, int nextY);

    public:
        // Constructor that takes in Initial Coordinates and 
        Move(int x, int y, int destX, int destY, Square* dest, Direction d);

        // Constructor that takes in two STRING COORDINATES (e.g. a1, e7, etc...)
        Move(string s, string d, vector<vector<Square>>& gameBoard);

        // Constructor that takes in a Move and Value
        Move(Move m, int val);

        // Checks whether Two Moves are Equal (The Same Coordinates)
        bool isEqual(Move& other);

        // Checks whether other has the same destination 
        bool isSameDestination(Move& other);

        // returns the initial X value
        int getInitX() { return initialX; }

        // returnsd the initial Y value
        int getInitY() { return initialY; }

        // returns the destination X value
        int getDestX() { return destinationX; }

        // returns the destination Y value
        int getDestY() { return destinationY; }

        // sets the value of a move based on ranking (used by Computer, not Human!)
        void setValue(int n) { moveValue = n; }

        // returns the Move's rank value
        int getValue() { return moveValue; }

        // returns the Direction of the Move
        Direction getDirection() { return moveDirection; }

        // returnds s pointer to the destination Square
        Square* getSquare() { return destSquare; }

};

#endif
