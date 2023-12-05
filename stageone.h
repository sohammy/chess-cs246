#ifndef STAGEONE_H
#define STAGEONE_H
#include "computer.h"

class StageOne : public Computer{
    public:
       Move doMove(Board& gameBoard, Colour team) override;
       int teamValueCalc(vector<Piece*> pieces) override {return 0;}
};

#endif
