#ifndef STAGETHREE_H
#define STAGETHREE_H
#include "computer.h"

class StageThree : public Computer{
    public:
        void makeMove(Board& gameBoard, Colour team) override {}
};

#endif
