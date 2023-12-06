#include "minimax.h"
#include <cstdlib>

Move maxOfMoves(vector<Move> moves) {
    int max = 0;
    int index = 0;
    int largestIndex = 0;
    for(Move m : moves) {
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

char autoChoosePromotionPiece() {
    int index = std::rand() % 10 + 1;
    if(index < 3) {
        return 'N';
    }
    return 'Q';
}

