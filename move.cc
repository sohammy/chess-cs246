#include "move.h"
#include <string>
using namespace std;

Direction Move::coordsToDirection(int x, int y, int nextX, int nextY) {
    if(nextX < x && nextY == y) return N;
    if(nextX > x && nextY == y) return S;
    if(nextX == x && nextY > y) return E;
    if(nextX == x && nextY < y) return W;
    if(nextX < x && nextY > y) return NE;
    if(nextX < x && nextY < y) return NW;
    if(nextX > x && nextY > y) return SE;
    if(nextX > x && nextY < y) return SW;
    return NONE;
}

int Move::letterToInt(char c) {
    if (c >= 'a' && c <= 'h') return c - 'a';
    return -1;
}

bool Move::isEqual(Move& other) {
    if(initialX == other.getInitX() &&
    initialY == other.getInitY() &&
    destinationX == other.getDestX() &&
    destinationY == other.getDestY() &&
    moveDirection == other.getDirection()) return true;
    return false;
}

bool Move::isSameDestination(Move& other) {
    if(destinationX == other.getDestX() && destinationY == other.getDestY()) {
        return true;
    }
    return false;
}

Move::Move(int x, int y, int destX, int destY, Square* dest, Direction d): 
    initialX{x}, initialY{y}, destinationX{destX}, destinationY{destY}, destSquare{dest}, moveDirection{d} {}

Move::Move(string m, string d, vector<vector<Square>>& gameBoard) {
    if (m.size() == 2 && d.size() == 2) {
        initialX = 8 - (m[1] - '0');
        initialY = letterToInt(m[0]);
        destinationX = 8 - (d[1] - '0');
        destinationY = letterToInt(d[0]);
        destSquare = &(gameBoard[destinationX][destinationY]);
        moveDirection = coordsToDirection(initialX, initialY, destinationX, destinationY);
    } else {
        initialX = initialY = destinationX = destinationY = -1;
    }
}

Move::Move(Move m, int val)
: initialX{m.getInitX()}, initialY{m.getInitY()}, destinationX{m.getDestX()}, 
destinationY{m.getDestY()}, moveValue{val}, destSquare{m.getSquare()}, moveDirection{m.getDirection()} {}
