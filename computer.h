#ifndef COMPUTER_H
#define COMPUTER_H
#include "player.h"
#include "move.h"
#include <vector>
using namespace std;

class Computer : public Player {
    public:
        Computer();
        virtual void makeMove(Board& gameBoard, Colour team) = 0;
};


#endif
