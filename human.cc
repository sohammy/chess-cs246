#include "human.h"
using namespace std;


Human::Human() {}

void Human::makeMove(Board& gameBoard, Colour team) { // add colour to this so that we can only move the right pieces
    string pieceSelected, destination;
    bool foundMove = false;

    while(!foundMove){
        cin >> pieceSelected >> destination;
        Move moveAttempted = Move(pieceSelected, destination, gameBoard.getBoard());

        Square* start = &gameBoard.getBoard()[moveAttempted.getInitX()][moveAttempted.getInitY()]; 
        Piece* piece = start->getPiece();

        if(team == piece->getColour()) {

            piece->calculateMoves();

            int successIndex = 0;
            vector<Move> possibleMoves = piece->getMoves();
            for(Move m : possibleMoves) {
                if (moveAttempted.isEqual(m)) { 
                    foundMove = true;
                    break;
                }
                ++successIndex;
            }
            
            if(foundMove) {
                Move successfulMove = possibleMoves[successIndex];
                Square* dest = successfulMove.getSquare();

                if(dest->getPiece() != nullptr) { 
                    cout << "There is a Piece There, We are Removing it" << endl;
                    gameBoard.removePiece(dest->getX(), dest->getY());
                }

                dest->removePiece();
                dest->addPiece(piece);
                piece->setSquare(dest);
                start->removePiece();
                piece->pieceMoved();
                dest->notifyDisplayObservers();
                start->notifyDisplayObservers();
                // cout << "error is in start->notifyPieceObservers" << endl;
                // start->notifyPieceObservers();
                // cout << "nvm error is in dest->notifyPieceObservers" << endl;
                // dest->notifyPieceObservers();
            } else {
                cout << "Please make a valid move" << endl;
            }
        } else {
            cout << "You can only select pieces from your team!" << endl;
        }
    }
}
