#ifndef HUMAN_H
#define HUMAN_H
#include "player.h"

class Human : public Player {
public:
    Human();
    void getMove(Board& gameBoard) override;
    ~Human() override;
};

#endif
