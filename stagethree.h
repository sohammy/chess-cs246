#ifndef STAGETHREE_H
#define STAGETHREE_H
#include "computer.h"

class StageThree : public Computer{
    public:
        Move doMove(Board& gameBoard, Colour team) override;
};

#endif
