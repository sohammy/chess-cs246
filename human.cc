#include "human.h"
using namespace std;


Human::Human() {}

void Human::makeMove(Board& gameBoard) {
    string pieceSelected, destination;
    bool foundMove = false;

    while(!foundMove){
        cin >> pieceSelected >> destination;
        Move moveAttempted = Move(pieceSelected, destination, gameBoard.getBoard());

        Square* start = &gameBoard.getBoard()[moveAttempted.getInitX()][moveAttempted.getInitY()]; 
        Piece* piece = start->getPiece();

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
            cout << "FOUND MOVE!!" << endl;
            Move successfulMove = possibleMoves[successIndex];
            Square* dest = successfulMove.getSquare();

            if(dest->getPiece() != nullptr) { // change to impl of square
                dest->removePiece();
            }
            dest->addPiece(piece);
            start->removePiece();
            piece->pieceMoved();
            dest->notifyDisplayObservers();
            start->notifyDisplayObservers();
            start->notifyPieceObservers();
            dest->notifyPieceObservers();
        } else {
            cout << "Please make a valid move" << endl;
        }
    }
}
