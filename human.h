#ifndef HUMAN_H
#define HUMAN_H
#include "player.h"

class Human : public Player {
    public:
        Human();
        void makeMove(Board& gameBoard, Colour team) override;
};

#endif
