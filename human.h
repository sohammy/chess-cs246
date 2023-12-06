#ifndef HUMAN_H
#define HUMAN_H
#include "player.h"

class Human : public Player {
    public:
        Human();

        // Allows Users to Make a Move on the PRIMARY gameboard
        void makeMove(Board& gameBoard, Colour team) override;
};

#endif
