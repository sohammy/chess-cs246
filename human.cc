#include "human.h"
using namespace std;


Human::Human() {}

void Human::makeMove(Board& gameBoard) {
    string pieceSelected, destination;
    bool foundMove = false;

    while(!foundMove){
        cin >> pieceSelected >> destination;
        Move moveAttempted = Move(pieceSelected, destination);

        vector<Move> possibleMoves = gameBoard.theBoard[moveAttempted.getInitX()][moveAttempted.getInitY()]->currPiece.getMoves();
        for(Move m : possibleMoves) {
            if (moveAttempted.isEqual(m)) { 
                foundMove = true; 
                break;
            }
        }

        if(foundMove) {
            if(gameBoard.theBoard[moveAttempted.getDestX()][moveAttempted.getDestY()].getCurrPiece() != nullptr) { // change to impl of square
                gameBoard.theBoard[moveAttempted.getDestX()][moveAttempted.getDestY()].removePiece();
            }
            gameBoard.theBoard[moveAttempted.getDestX()][moveAttempted.getDestY()].addPiece(
                gameBoard.theBoard[moveAttempted.getInitX()][moveAttempted.getInitY()].getCurrPiece()
            );
            gameBoard.theBoard[moveAttempted.getInitX()][moveAttempted.getInitY()].removePiece();
        } else {
            cout << "Please a valid move" << endl;
        }
    }
}
