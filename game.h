#include <memory>
#include <iostream>

#include "board.h"

class Game {
    bool whoseTurn;
    int whiteScore;
    int blackScore;

public:
    void play(Board& myBoard);
    void gameStart();
    bool hasWon();
};