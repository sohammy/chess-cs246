#include "stageone.h"
#include <cstdlib>

Move StageOne::doMove(Board &gameBoard, Colour team) {
    vector<Piece *> teamPieces;
    if (team == WHITE) {
        for (unsigned int i = 0; i < gameBoard.availableWhites.size(); ++i) {
            teamPieces.emplace_back(gameBoard.availableWhites[i].get());
        }
    } else {
        for (unsigned int i = 0; i < gameBoard.availableBlacks.size(); ++i) {
            teamPieces.emplace_back(gameBoard.availableBlacks[i].get());
        }
    }

    vector<Move> allMoves;
    for (Piece *p : teamPieces)
    {
        p->calculateMoves();
        for (Move m : p->getMoves())
        {
            allMoves.emplace_back(m);
        }
    }

    int numMoves = allMoves.size();
    int index = std::rand() % numMoves + 0;

    Move ourMove = allMoves[index];
    return ourMove;
}
