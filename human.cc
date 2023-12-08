#include "human.h"
using namespace std;


Human::Human() {}

void Human::makeMove(Board& gameBoard, Colour team) { // add colour to this so that we can only move the right pieces
    string myInput, pieceSelected, destination;
    bool foundMove = false;

    while(!foundMove){
        
        cin >> myInput;

        if (myInput == "resign") {
            if (team == Colour::BLACK) {
                gameBoard.blackLose = true;
                gameBoard.whiteLose = false;
                break;
            }
            gameBoard.whiteLose = true;
            break;
        } else if (myInput == "move") {
            cin >> pieceSelected;
            cin >> destination;
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
                                if (piece->getY() - dest->getY() == 2) {
                                    King* myKing = dynamic_cast<King*>(piece);
                                    if (myKing->canCastleLong()) {
                                        canCastleLong = true;
                                    }
                                }

                                if (piece->getY() - dest->getY() == -2) {
                                    King* myKing = dynamic_cast<King*>(piece);
                                    if (myKing->canCastleShort()) {
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

                            if(toupper(piece->getPieceName()) != 'K' && gameBoard.isMate(team) ) {
                                dest->removePiece();
                                dest->addPiece(opposingPiece);
                                start->addPiece(piece);
                                foundMove = false;
                            } else if(enPassanting) {
                                dest->removePiece();
                                dest->addPiece(opposingPiece);
                                if(team == WHITE) {
                                    gameBoard.removePiece(dest->getX() + 1, dest->getY());
                                    gameBoard.getBoard()[dest->getX() + 1][dest->getY()].removePiece();
                                } else {
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
                                piece->setSquare(dest);
                                dest->addPiece(piece);
                                start->removePiece();
                                piece->pieceMoved();
                            
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
                                piece->setSquare(dest);
                                dest->addPiece(piece);
                                start->removePiece();
                                piece->pieceMoved();
                            
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
}
