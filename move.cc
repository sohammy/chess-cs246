#include "move.h"
#include <string>
using namespace std;

Direction Move::coordsToDirection(int x, int y, int nextX, int nextY) {
    if(nextX == x && nextY < y) return N;
    if(nextX == x && nextY > y) return S;
    if(nextX > x && nextY == y) return E;
    if(nextX < x && nextY == y) return W;
    if(nextX > x && nextY < y) return NE;
    if(nextX < x && nextY < y) return NW;
    if(nextX > x && nextY > y) return SE;
    if(nextX < x && nextY > y) return SW;
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
}

Move::Move(int x, int y, int destX, int destY, Direction d, Square* dest): 
    initialX{x}, initialY{y}, destinationX{destX}, destinationY{destY}, moveDirection{d}, destSquare{dest} {}

Move::Move(string m, string d, vector<vector<Square>>& gameBoard) {
    if (m.size() == 2 && d.size() == 2) {
        initialX = letterToInt(m[0]);
        initialY = 8 - (m[1] - '0');
        destinationX = letterToInt(d[0]);
        destinationY = 8 - (d[1] - '0');
    } else {
        // Add some error handling for invalid string formats
        // Set default values or throw an exception, depending on your error-handling strategy
        initialX = initialY = destinationX = destinationY = -1;
    }
    destSquare = &(gameBoard[destinationX][destinationY]);
    moveDirection = coordsToDirection(initialX, initialY, destinationX, destinationY);
}
