#ifndef MOVE_H
#define MOVE_H
#include <string>
#include "square.h"
using namespace std;


enum Direction{N, E, S, W, NE, SE, SW, NW};

class Move {
    int initialX;
    int initialY;
    int destinationX;
    int destinationY;
    shared_ptr<Square> destSquare;
    Direction d;

    int letterToInt(char c);

    public:
        Move(int x, int y, int destX, int destY, Direction d, shared_ptr<Square> dest);
        Move(string s, string d);
        bool isEqual(const Move& other);
        int getInitX() { return initialX; }
        int getInitY() { return initialY; }
        int getDestX() { return destinationX; }
        int getDestY() { return destinationY; }
        Direction getDirection() { return d; }
        shared_ptr<Square> getSquare() { return destSquare; }


};

#endif
