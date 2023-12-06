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
#include "stagefive.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"

class Game {
    unique_ptr<Player> white;
    unique_ptr<Player> black;

    std::shared_ptr<TextDisplay> td = make_shared<TextDisplay>();
    std::shared_ptr<GraphicsDisplay> gd;

    bool whoseTurn;
    double whiteScore = 0;
    double blackScore = 0;

public:
    void gameStart();
    void play(Board& myBoard);
    void setTurn(char c);
    double getWhiteScore() {return whiteScore;}
    double getBlackScore() {return blackScore;}
};

#endif