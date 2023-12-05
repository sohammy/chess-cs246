#include "stagetwo.h"

Move StageTwo::doMove(Board& gameBoard, Colour team) {
    return generateMove(gameBoard, team, 1, team, INTREALLLOW, INTREALLYHIGH);
}
