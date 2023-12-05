#include "stagetwo.h"

Move StageTwo::doMove(Board& gameBoard, Colour team) {
    return generateMove(gameBoard, team, 1, team);
}

int StageTwo::teamValueCalc(vector<Piece*> pieces) {
    int sum = 0;
    for(Piece* p : pieces) {
        if(toupper(p->getPieceName()) == 'K') {
            sum += 1000;
        } else if(toupper(p->getPieceName()) == 'Q') {
            sum += 100;
        } else if(toupper(p->getPieceName()) == 'B') {
            sum += 70;
        } else if(toupper(p->getPieceName()) == 'R') {
            sum += 50;
        } else if(toupper(p->getPieceName()) == 'N') {
            sum += 40;
        } else if(toupper(p->getPieceName()) == 'P') {
            sum += 10;
        } 
    }
    return sum;
}
