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
    int moveValue = 0;
    Square* destSquare;
    Direction moveDirection;

    int letterToInt(char c);
    Direction coordsToDirection(int x, int y, int nextX, int nextY);

    public:
        Move(int x, int y, int destX, int destY, Square* dest, Direction d);
        Move(string s, string d, vector<vector<Square>>& gameBoard);
        bool isEqual(Move& other);
        bool isSameDestination(Move& other);
        int getInitX() { return initialX; }
        int getInitY() { return initialY; }
        int getDestX() { return destinationX; }
        int getDestY() { return destinationY; }
        void setValue(int n) {moveValue = n;}
        int getValue() { return moveValue; }
        Direction getDirection() { return moveDirection; }
        Square* getSquare() { return destSquare; }

};

#endif
