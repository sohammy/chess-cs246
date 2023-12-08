#include "stagethree.h"

Move StageThree::doMove(Board& gameBoard, Colour team) {
    return generateMove(gameBoard, team, 2, team, INTREALLLOW, INTREALLYHIGH);
}
