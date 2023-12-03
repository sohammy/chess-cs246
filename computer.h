#ifndef COMPUTER_H
#define COMPUTER_H
#include "player.h"

class Computer : public Player {
    public:
        Computer();
        void makeMove(Board& gameBoard, Colour team) override;
};


#endif
