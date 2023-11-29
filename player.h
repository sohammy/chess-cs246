#ifndef PLAYER_H
#define PLAYER_H
#include "board.h"

class Player {
    public:
        Player();
        virtual void getMove(Board& gameBoard) = 0;
        virtual ~Player();
};

#endif
