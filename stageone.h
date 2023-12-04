#ifndef STAGEONE_H
#define STAGEONE_H
#include "computer.h"

class StageOne : public Computer{
    public:
       void makeMove(Board& gameBoard, Colour team) override;
};

#endif
