#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include "move.h"
#include "board.h"
#include "piece.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "king.h"
#include "queen.h"
#include "square.h"

class Player {
    public:
        Player();
        virtual void makeMove(Board& gameBoard, Colour team) = 0;
 };

#endif
