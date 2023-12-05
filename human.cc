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
            cout << moveAttempted.getInitX() << moveAttempted.getInitY() << moveAttempted.getDestX() << moveAttempted.getDestY() << endl;
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
                        bool canCastleLong = false;
                        bool canCastleShort = false;

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

                        if(toupper(piece->getPieceName()) == 'K') {
                            cout << "Here in K" << endl;
                            
                            cout << "Piece Y is " << piece->getY() << endl;
                            cout << "Dest Y is " << dest->getY() << endl;

                            if (piece->getY() - dest->getY() >= 0) {
                                King* myKing = dynamic_cast<King*>(piece);
                                if (myKing->canCastleLong()) {
                                    cout << "Here in KLong" << endl;
                                    canCastleLong = true;
                                }
                            }

                            if (piece->getY() - dest->getY() <= 0) {
                                King* myKing = dynamic_cast<King*>(piece);
                                if (myKing->canCastleShort()) {
                                    cout << "Here in KShort" << endl;
                                    canCastleShort = true;
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

                        if(toupper(piece->getPieceName()) != 'K' && gameBoard.isMate() ) {
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
                        } else if (canCastleLong) {
                            
                            cout << "In canCastleLong" << endl;
                            piece->setSquare(dest);
                            dest->addPiece(piece);
                            start->removePiece();
                            piece->pieceMoved();
                       
                            
                            cout << "The Piece Is " << gameBoard.getBoard()[dest->getX()][dest->getY() - 2].getPiece()->getPieceName() << endl;
                        
                            gameBoard.getBoard()[dest->getX()][dest->getY() - 2].getPiece()->setSquare(&gameBoard.getBoard()[dest->getX()][dest->getY() + 1]);
                            gameBoard.getBoard()[dest->getX()][dest->getY() + 1].addPiece(gameBoard.getBoard()[dest->getX()][dest->getY() - 2].getPiece());
                            gameBoard.getBoard()[dest->getX()][dest->getY() - 2].removePiece();
                            gameBoard.getBoard()[dest->getX()][dest->getY() + 1].getPiece()->pieceMoved();

                            dest->notifyDisplayObservers();
                            start->notifyDisplayObservers();
                            gameBoard.getBoard()[dest->getX()][dest->getY() + 1].notifyDisplayObservers();
                            gameBoard.getBoard()[dest->getX()][dest->getY() - 2].notifyDisplayObservers();

                            piece->calculateMoves();
                            gameBoard.getBoard()[dest->getX()][dest->getY() + 1].getPiece()->calculateMoves();

                        } else if (canCastleShort) {

                            cout << "In canCastleShort " << endl;
                            piece->setSquare(dest);
                            dest->addPiece(piece);
                            start->removePiece();
                            piece->pieceMoved();

                            cout << "The Piece Is " << gameBoard.getBoard()[dest->getX()][dest->getY() + 1].getPiece()->getPieceName() << endl;
                        
                            gameBoard.getBoard()[dest->getX()][dest->getY() + 1].getPiece()->setSquare(&gameBoard.getBoard()[dest->getX()][dest->getY() - 1]);
                            gameBoard.getBoard()[dest->getX()][dest->getY() - 1].addPiece(gameBoard.getBoard()[dest->getX()][dest->getY() + 1].getPiece());
                            gameBoard.getBoard()[dest->getX()][dest->getY() + 1].removePiece();
                            gameBoard.getBoard()[dest->getX()][dest->getY() - 1].getPiece()->pieceMoved();

                            dest->notifyDisplayObservers();
                            start->notifyDisplayObservers();
                            gameBoard.getBoard()[dest->getX()][dest->getY() + 1].notifyDisplayObservers();
                            gameBoard.getBoard()[dest->getX()][dest->getY() - 1].notifyDisplayObservers();

                            piece->calculateMoves();
                            gameBoard.getBoard()[dest->getX()][dest->getY() - 1].getPiece()->calculateMoves();

                        }
                        else {
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
