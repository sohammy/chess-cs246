#ifndef STAGETWO_H
#define STAGETWO_H
#include "computer.h"

class StageTwo : public Computer{
    public:
        Move doMove(Board& gameBoard, Colour team) override;
        int teamValueCalc(vector<Piece*> pieces) override;
};

#endif
