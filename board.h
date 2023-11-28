#ifndef BOARD_H
#define BOARD_H

#include <vector>

using namespace std;
// #include "square.h"

class Board {
    vector<vector<char>> theBoard;
    vector<char> aliveBlacks;
    vector<char> aliveWhites;

public:
    void clearBoard();
    void initializeBoard();
};


#endif
