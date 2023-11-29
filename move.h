#ifndef MOVE_H
#define MOVE_H
#include <string>
using namespace std;

class Move {
    int initialX;
    int initialY;
    int destinationX;
    int destinationY;
    int letterToInt(char c);
    int pointsForMove = 0;

    public:
        Move(int x, int y, int destX, int destY);
        Move(string s, string d);
        bool isEqual(const Move& other);
        int getInitX() { return initialX; }
        int getInitY() { return initialY; }
        int getDestX() { return destinationX; }
        int getDestY() { return destinationY; }
};

#endif
