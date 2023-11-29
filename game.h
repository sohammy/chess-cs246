#ifndef BOARD_H
#define BOARD_H

#include <memory>
#include <iostream>

#include "board.h"
#include "player.h"
#include "textdisplay.h"

class Game {

    unique_ptr<Player> white;
    unique_ptr<Player> black;

    bool whoseTurn;
    int whiteScore;
    int blackScore;

public:
    void gameStart();
    void play(Board& myBoard);
    void setTurn(char c);
    int whoWon();
};

#endif