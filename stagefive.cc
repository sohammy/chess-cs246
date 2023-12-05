#include "stagefive.h"

Move StageFive::doMove(Board& gameBoard, Colour team) {
    return generateMove(gameBoard, team, 6, team, INTREALLLOW, INTREALLYHIGH);
}
