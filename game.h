#ifndef GAME_H
#define GAME_H

#include <memory>
#include <iostream>

#include "board.h"
#include "player.h"
#include "human.h"
#include "computer.h"
#include "stageone.h"
#include "stagetwo.h"
#include "stagethree.h"
#include "stagefour.h"
#include "textdisplay.h"

class Game {
    unique_ptr<Player> white;
    unique_ptr<Player> black;

    std::shared_ptr<TextDisplay> td;

    bool whoseTurn;
    int whiteScore;
    int blackScore;

public:
    void gameStart();
    void play(Board& myBoard);
    void setTurn(char c);
};

#endif