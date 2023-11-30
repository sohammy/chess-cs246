#include "move.h"
#include <string>
using namespace std;

int Move::letterToInt(char c) {
    if (c >= 'a' && c <= 'h') return c - 'a';
    return -1;
}

bool Move::isEqual(const Move& other) {
    if(initialX == other.initialX &&
    initialY == other.initialY &&
    destinationX == other.destinationX &&
    destinationY == other.destinationY) return true;
    return false;
}

Move::Move(int x, int y, int destX, int destY, Direction d, Square* dest): 
    initialX{x}, initialY{y}, destinationX{destX}, destinationY{destY}, d{d}, destSquare{dest} {
        
    }

Move::Move(string m, string d) {
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
}
