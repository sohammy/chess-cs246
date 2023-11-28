//#include "player.h"
//#include "board.h"


#include <iostream>
#include <string>
#include <memory>

using namespace std;

class Game {

    //Board gameBoard;


    int testCounter; // THIS IS A TEST
    bool whoseTurn = 0; // if 0, then White; if 1, then Black

    public:
        void play(string whitePlayer, string blackPlayer);
        bool hasWon();

};

