#ifndef STAGEFIVE_H
#define STAGEFIVE_H
#include "computer.h"

class StageFive : public Computer {
    public:
        Move doMove(Board& gameBoard, Colour team) override;
};

#endif
