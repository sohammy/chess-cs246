#include "stageone.h"
#include <cstdlib>

void StageOne::makeMove(Board &gameBoard, Colour team) {
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

    bool foundMove = false;
    while(!foundMove) {
        int numMoves = allMoves.size();
        int index = std::rand() % numMoves + 0;

        Move ourMove = allMoves[index];
        if(ourMove.getInitX() < 8 && ourMove.getInitY() < 8 && ourMove.getDestX() < 8 && ourMove.getDestY() < 8) {
            Square* start = &gameBoard.getBoard()[ourMove.getInitX()][ourMove.getInitY()]; 
            Piece* piece = start->getPiece();

            Square *dest = ourMove.getSquare();
            bool enPassanting = false;

            if (toupper(piece->getPieceName()) == 'P'){
                if (piece->getY() != dest->getY()){
                    if (dest->canEnPassant() && dest->getPiece() == nullptr){
                        enPassanting = true;
                    }
                }
                else if (abs(piece->getX() - dest->getX()) == 2){
                    if (team == WHITE){
                        gameBoard.getBoard()[piece->getX() - 1][piece->getY()].turnOnEnPassant();
                    } else {
                        gameBoard.getBoard()[piece->getX() + 1][piece->getY()].turnOnEnPassant();
                    }
                }
            }

            Piece* opposingPiece = nullptr;
            if(dest->getPiece() != nullptr) {
                            opposingPiece = dest->getPiece();
                        }
                        start->removePiece();
                        dest->removePiece();
                        dest->addPiece(piece);

                        if(gameBoard.isMate()) {
                            dest->removePiece();
                            dest->addPiece(opposingPiece);
                            start->addPiece(piece);
                            foundMove = false;
                        } else if(enPassanting) {
                            dest->removePiece();
                            dest->addPiece(opposingPiece);
                            if(team == WHITE) {
                                cout << "There is a Piece There, We are Removing it" << endl;
                                gameBoard.removePiece(dest->getX() + 1, dest->getY());
                                gameBoard.getBoard()[dest->getX() + 1][dest->getY()].removePiece();
                            } else {
                                cout << "There is a Piece There, We are Removing it" << endl;
                                gameBoard.removePiece(dest->getX() - 1, dest->getY());
                                gameBoard.getBoard()[dest->getX() - 1][dest->getY()].removePiece();
                            }
                            dest->addPiece(piece);
                            piece->setSquare(dest);
                            piece->pieceMoved();
                            dest->notifyDisplayObservers();
                            start->notifyDisplayObservers();
                            piece->calculateMoves();
                        } else {
                            dest->removePiece();
                            dest->addPiece(opposingPiece);
                            if(dest->getPiece() != nullptr) { 
                                    cout << "There is a Piece There, We are Removing it" << endl;
                                    gameBoard.removePiece(dest->getX(), dest->getY());
                            }
                            dest->removePiece();
                            dest->addPiece(piece);
                            piece->setSquare(dest);
                            piece->pieceMoved();
                            dest->notifyDisplayObservers();
                            start->notifyDisplayObservers();
                            piece->calculateMoves();
                        }
        }
    }
}
