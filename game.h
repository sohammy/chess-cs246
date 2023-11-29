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
    void play(Board& myBoard);
    void gameStart();
    void setTurn(char c);
    int whoWon();
};

#endif