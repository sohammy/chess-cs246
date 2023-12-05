#include "minimax.h"

Move maxOfMoves(vector<Move> moves) {
    int max = 0;
    int index = 0;
    int largestIndex = 0;
    for(Move m : moves) {
        cout << index << endl;
        if(m.getValue() > max) {
            max = m.getValue();
            cout << max << " current max value" << endl;
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

int getPieceValue(Piece* p) {
    char pieceName = toupper(p->getPieceName());
    if (pieceName == 'K') {
        return 100;
    } else if (pieceName == 'Q') {
        return 20;
    } else if (pieceName == 'R') {
        return 6;
    } else if (pieceName == 'B') {
        return 4;
    } else if (pieceName == 'N') {
        return 3;
    } else if (pieceName == 'P') {
        return 1;
    }
    return 0;
}

