#ifndef PLAYER_H
#define PLAYER_H

class Player {
    public:
        Player();
        virtual void getMove() = 0;
        virtual ~Player();
};

#endif
