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
                    
                    if(foundMove) {
                        Move successfulMove = possibleMoves[successIndex];
                        Square* dest = successfulMove.getSquare();
                        bool enPassanting = false;

                        

                        if(toupper(piece->getPieceName()) == 'P') {
                            cout << "Detected Pawn Movement..." << endl;
                            if(piece->getY() != dest->getY()) {
                                cout << "Pawn is attacking" << endl;
                                if(dest->canEnPassant() && dest->getPiece() == nullptr) {
                                    enPassanting = true;
                                    cout << "We are en passanting" << endl;
                                }
                            } else if (abs(piece->getX() - dest->getX()) == 2) {
                                cout << "We moved 2" << endl;
                                if(team == WHITE) {
                                    gameBoard.getBoard()[piece->getX() - 1][piece->getY()].turnOnEnPassant();
                                    cout << "White piece is now En Passantable" << endl;
                                } else {
                                    gameBoard.getBoard()[piece->getX() + 1][piece->getY()].turnOnEnPassant();
                                    cout << "Black piece is now En Passantable" << endl;
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
                                cout << "White piece is now En Passantable" << endl;
                            } else {
                                cout << "There is a Piece There, We are Removing it" << endl;
                                gameBoard.removePiece(dest->getX() - 1, dest->getY());
                                gameBoard.getBoard()[dest->getX() - 1][dest->getY()].removePiece();
                                cout << "Black piece is now En Passantable" << endl;
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
