#ifndef STAGEFOUR_H
#define STAGEFOUR_H
#include "computer.h"

class StageFour : public Computer{
    public:
        void makeMove(Board& gameBoard, Colour team) override {}
};

#endif
