#include "stagefour.h"

Move StageFour::doMove(Board& gameBoard, Colour team) {
    return generateMove(gameBoard, team, 3, team, INTREALLLOW, INTREALLYHIGH);
}
