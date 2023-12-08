#ifndef STAGEFOUR_H
#define STAGEFOUR_H
#include "computer.h"

class StageFour : public Computer{
    public:
        Move doMove(Board& gameBoard, Colour team) override;
};

#endif
