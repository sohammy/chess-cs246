#ifndef STAGEFOUR_H
#define STAGEFOUR_H
#include "computer.h"

class StageFour : public Computer{
    public:
        Move doMove(Board& gameBoard, Colour team) override { return Move(-1,-1,-1,-1,nullptr,N);}
        int teamValueCalc(vector<Piece*> pieces) override {return 0;}
};

#endif
