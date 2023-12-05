#include "minimax.h"

Move maxOfMoves(vector<Move> moves) {
    int max = 0;
    int index = 0;
    int largestIndex = 0;
    for(Move m : moves) {
        cout << index << endl;
        if(m.getValue() > max) {
            max = m.getValue();
            largestIndex = index;
        }
        ++index;
    }

    return moves[largestIndex];
}

Move minOfMoves(vector<Move> moves) {
    int min = 0;
    int index = 0;
    int smallestIndex = 0;
    for(Move m : moves) {
        if(m.getValue() < min) {
            min = m.getValue();
            smallestIndex = index;
        }
        ++index;
    }

    return moves[smallestIndex];
}
