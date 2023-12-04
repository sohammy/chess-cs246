#include "human.h"
using namespace std;


Human::Human() {}

void Human::makeMove(Board& gameBoard, Colour team) { // add colour to this so that we can only move the right pieces
    string pieceSelected, destination;
    bool foundMove = false;

    while(!foundMove){
        cin >> pieceSelected >> destination;
        if(pieceSelected.length() == 2 && 
        destination.length() == 2 &&
        pieceSelected[0] <= 'h' &&
        pieceSelected[0] >= 'a' &&
        pieceSelected[1] >= '1' &&
        pieceSelected[1] <= '8' &&
        destination[0] <= 'h' &&
        destination[0] >= 'a' &&
        destination[1] >= '1' &&
        destination[1] <= '8') {
            Move moveAttempted = Move(pieceSelected, destination, gameBoard.getBoard());

            Square* start = &gameBoard.getBoard()[moveAttempted.getInitX()][moveAttempted.getInitY()]; 
            Piece* piece = start->getPiece();

            if(piece != nullptr) {

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
                    
                    if(foundMove) { // Once we found move
                        Move successfulMove = possibleMoves[successIndex];
                        Square* dest = successfulMove.getSquare();
                        bool enPassanting = false;

                        if(toupper(piece->getPieceName()) == 'P') {
                            if(piece->getY() != dest->getY()) {
                                if(dest->canEnPassant() && dest->getPiece() == nullptr) {
                                    enPassanting = true;
                                }
                            } else if (abs(piece->getX() - dest->getX()) == 2) {
                                if(team == WHITE) {
                                    gameBoard.getBoard()[piece->getX() - 1][piece->getY()].turnOnEnPassant();
                                } else {
                                    gameBoard.getBoard()[piece->getX() + 1][piece->getY()].turnOnEnPassant();
                                }
                            }
                        }

                        start->removePiece();

                        if(gameBoard.isMate()) {
                            start->addPiece(piece);
                            foundMove = false;
                        } else if(enPassanting) {
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
                        
                    } else {
                        cout << "Please make a valid move" << endl;
                    }
                } else {
                    cout << "You can only select pieces from your team!" << endl;
                }
            } else {
                cout << "Please pick a valid square" << endl;
            }
        } else {
            cout << "Please enter valid coordinates" << endl;
        }
    }
}
