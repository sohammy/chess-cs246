#ifndef STAGETWO_H
#define STAGETWO_H
#include "computer.h"

class StageTwo : public Computer{
    public:
        void makeMove(Board& gameBoard, Colour team) override {}
};

#endif
