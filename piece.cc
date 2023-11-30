#include "piece.h"

void Piece::setColour(char c) {
    if (c == 'w') pieceColour = white;
    if (c == 'b') pieceColour = black;
}
