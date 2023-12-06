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

    // Starts the Game -- Acts as 'the Hub' that interacts with Board Functionality
    void gameStart();

    // Allows users to PLAY CHESS on either a User Created or Pre-Initialized Board
    void play(Board& myBoard);

    // Sets the Game Turn to the Team Colour, c
    void setTurn(char c);

    // Returns White Score
    double getWhiteScore() {return whiteScore;}

    // Returns Black Score
    double getBlackScore() {return blackScore;}
};

#endif

