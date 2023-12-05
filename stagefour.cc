#include "stagefour.h"

Move StageFour::doMove(Board& gameBoard, Colour team) {
    return generateMove(gameBoard, team, 3, team, -10000000, 10000000);
}
