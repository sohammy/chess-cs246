#ifndef STAGEONE_H
#define STAGEONE_H
#include "computer.h"

class StageOne : public Computer{
    public:
       Move doMove(Board& gameBoard, Colour team) override;
};

#endif
