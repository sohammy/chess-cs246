#include "human.h"
using namespace std;


Human::Human() {}

void Human::makeMove(Board& gameBoard) {
    string pieceSelected, destination;
    bool foundMove = false;

    while(!foundMove){
        cin >> pieceSelected >> destination;
        Move moveAttempted = Move(pieceSelected, destination, gameBoard.getBoard());

        vector<Move> possibleMoves = gameBoard.getBoard()[moveAttempted.getInitX()][moveAttempted.getInitY()].getPiece()->getMoves();
        for(Move m : possibleMoves) {
            if (moveAttempted.isEqual(m)) { 
                foundMove = true; 
                break;
            }
        }

        if(foundMove) {
            if(gameBoard.getBoard()[moveAttempted.getDestX()][moveAttempted.getDestY()].getPiece() != nullptr) { // change to impl of square
                gameBoard.getBoard()[moveAttempted.getDestX()][moveAttempted.getDestY()].removePiece();
            }
            gameBoard.getBoard()[moveAttempted.getDestX()][moveAttempted.getDestY()].addPiece(
                gameBoard.getBoard()[moveAttempted.getInitX()][moveAttempted.getInitY()].getPiece()
            );

            gameBoard.getBoard()[moveAttempted.getInitX()][moveAttempted.getInitY()].removePiece();
            gameBoard.getBoard()[moveAttempted.getDestX()][moveAttempted.getDestY()].getPiece()->pieceMoved();
            gameBoard.getBoard()[moveAttempted.getDestX()][moveAttempted.getDestY()].notifyDisplayObservers();
            gameBoard.getBoard()[moveAttempted.getInitX()][moveAttempted.getInitY()].notifyDisplayObservers();
            gameBoard.getBoard()[moveAttempted.getInitX()][moveAttempted.getInitY()].notifyPieceObservers();
            gameBoard.getBoard()[moveAttempted.getDestX()][moveAttempted.getDestY()].notifyPieceObservers();
        } else {
            cout << "Please make a valid move" << endl;
        }
    }
}
