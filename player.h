#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include "move.h"
#include "board.h"
#include "piece.h"
#include "square.h"

class Player {
    public:
        Player();
        virtual void makeMove(Board& gameBoard) = 0;
 };

#endif
