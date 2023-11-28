#ifndef GAME_H
#define GAME_H

#include "board.h"

//#include "player.h"

#include <iostream>
#include <string>
#include <memory>

using namespace std;

class Game {

    Board gameBoard;

    int testCounter; // THIS IS A TEST
    bool whoseTurn = 0; // if 0, then White; if 1, then Black

    public:
        void play(string whitePlayer, string blackPlayer);
        void setup();
        bool hasWon();
    
};

#endif
