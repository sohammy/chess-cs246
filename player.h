#ifndef PLAYER_H
#define PLAYER_H
#include "board.h"

class Player {
    public:
        Player();
        virtual void makeMove(Board& gameBoard) = 0;
 };

#endif
