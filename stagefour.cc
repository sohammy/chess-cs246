#include "stagefour.h"

Move StageFour::doMove(Board& gameBoard, Colour team) {
    return generateMove(gameBoard, team, 4, team, INTREALLLOW, INTREALLYHIGH);
}
