#include "stagefive.h"

Move StageFive::doMove(Board& gameBoard, Colour team) {
    return generateMove(gameBoard, team, 6, team, -10000000, 10000000);
}
