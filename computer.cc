#include "computer.h"

Computer::Computer() {}

//
//
//

Colour getOtherTeam(Colour c) {
    if(c == WHITE) {
        return BLACK; 
    }
    return WHITE;
}

//
//
//

int Computer::teamValueCalc(Board& gameBoard, Colour team) {
    int sum = 0;
    for(unsigned int i = 0; i < gameBoard.getBoard().size(); ++i) {
        for(unsigned int j = 0; j < gameBoard.getBoard()[i].size(); ++j) {
            if(gameBoard.getBoard()[i][j].getPiece() != nullptr) {
                Piece* p = gameBoard.getBoard()[i][j].getPiece();
                if(toupper(p->getPieceName()) == 'K') {
                    if(p->getColour() == team) {
                        sum += 1000;
                    } else {
                        sum -= 1000;
                    }
                } else if(toupper(p->getPieceName()) == 'Q') {
                    if(p->getColour() == team) {
                        sum += 100;
                    } else {
                        sum -= 100;
                    }
                } else if(toupper(p->getPieceName()) == 'B') {
                    if(p->getColour() == team) {
                        sum += 70;
                    } else {
                        sum -= 70;
                    }
                } else if(toupper(p->getPieceName()) == 'R') {
                    if(p->getColour() == team) {
                        sum += 50;
                    } else {
                        sum -= 50;
                    }
                } else if(toupper(p->getPieceName()) == 'N') {
                    if(p->getColour() == team) {
                        sum += 40;
                    } else {
                        sum -= 40;
                    }
                } else if(toupper(p->getPieceName()) == 'P') {
                    if(p->getColour() == team) {
                        sum += 10;
                    } else {
                        sum -= 10;
                    }
                } 
            }
        }
    }
    return sum;
}

//
//
//

bool isValidMove(Move m) {
    if(m.getDestX() <= 7 && m.getDestX() >= 0 && m.getDestY() <= 7 && m.getDestY() >=0
    && m.getInitX() <= 7 && m.getInitX() >= 0 && m.getInitY() <= 7 && m.getInitY() >=0) return true;
    return false;
}

//
//
//

vector<Piece*> getAllPieces(Colour c, Board& gameBoard) {
    vector<Piece*> pieces;
    for(unsigned int i = 0; i < gameBoard.getBoard().size() ; ++i) {
        for(unsigned int j = 0; j < gameBoard.getBoard()[i].size() ; ++j) {
            if(gameBoard.getBoard()[i][j].getPiece() != nullptr) {
                Piece* p = gameBoard.getBoard()[i][j].getPiece();
                if(p->getColour() == c) {
                    pieces.emplace_back(p);
                }
            }
        }
    }
    return pieces;
}

//
//
//

vector<Move> Computer::allMoves(Colour c, Board& gameBoard) {
    vector<Piece*> pieces = getAllPieces(c, gameBoard);
    vector<Move> allMoves;
    for(Piece* p : pieces) {
        p->calculateMoves();
        vector<Move> moves = p->getMoves();
        for(Move m : moves) {
            allMoves.emplace_back(m);
        }
    }
    return allMoves;
}

//
//
//

void Computer::simulateMove(Board& gameBoard, Move m, Colour team) {
    attackPiece = nullptr;
    killedPiece = '0';
    startSquare = nullptr;
    killedPieceSquare = nullptr;
    attackPieceDest = nullptr;

        Square* start = &gameBoard.getBoard()[m.getInitX()][m.getInitY()];
        Piece* piece = start->getPiece();

        Square *dest = m.getSquare();
        bool enPassanting = false;

        this->attackPiece = piece;
        this->startSquare = start;
        this->attackPieceDest = dest;

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
            this->killedPiece = opposingPiece->getPieceName();
            this->killedPieceSquare = dest;
        }
        start->removePieceWithoutObservers();
        dest->removePieceWithoutObservers();
        dest->addPieceWithoutObservers(piece);

        if(toupper(piece->getPieceName()) != 'K' && gameBoard.isMate()) {
            dest->removePieceWithoutObservers();
            dest->addPieceWithoutObservers(opposingPiece);
            start->addPieceWithoutObservers(piece);
        } else if(enPassanting) {
            dest->removePieceWithoutObservers();
            dest->addPieceWithoutObservers(opposingPiece);
            if(team == WHITE) {
                this->killedPieceSquare = &gameBoard.getBoard()[dest->getX() + 1][dest->getY()];
                this->killedPiece = killedPieceSquare->getPiece()->getPieceName();
                gameBoard.removePiece(dest->getX() + 1, dest->getY());
                gameBoard.getBoard()[dest->getX() + 1][dest->getY()].removePieceWithoutObservers();
            } else {
                this->killedPieceSquare = &gameBoard.getBoard()[dest->getX() - 1][dest->getY()];
                this->killedPiece = killedPieceSquare->getPiece()->getPieceName();
                gameBoard.removePiece(dest->getX() - 1, dest->getY());
                gameBoard.getBoard()[dest->getX() - 1][dest->getY()].removePieceWithoutObservers();
            }
            dest->addPieceWithoutObservers(piece);
            piece->setSquare(dest);
            piece->pieceMoved();
            piece->calculateMoves();
        } else {
            dest->removePieceWithoutObservers();
            dest->addPieceWithoutObservers(opposingPiece);
            if(dest->getPiece() != nullptr) {
                this->killedPiece = dest->getPiece()->getPieceName();
                this->killedPieceSquare = dest; 
                gameBoard.removePiece(dest->getX(), dest->getY());
            }
            dest->addPieceWithoutObservers(piece);
            piece->setSquare(dest);
            piece->pieceMoved();
            piece->calculateMoves();
        }

}

//
//
//

void Computer::undoMove(Board& gameBoard, Move m, Colour team) {
    Piece* pieceBack = nullptr;
    if(killedPiece != '0') {
        unique_ptr<Piece> p = gameBoard.makePiece(killedPiece);
        if(team == WHITE) {
            gameBoard.availableWhites.emplace_back(move(p));
            pieceBack = gameBoard.availableWhites.back().get();
            pieceBack->setColour('w');
        } else {
            gameBoard.availableBlacks.emplace_back(move(p));
            pieceBack = gameBoard.availableBlacks.back().get();
            pieceBack->setColour('b');
        }
    }
    attackPieceDest->removePieceWithoutObservers();
    startSquare->addPieceWithoutObservers(attackPiece);
    attackPiece->setSquare(startSquare);

    if(pieceBack != nullptr && killedPieceSquare != nullptr) {
        killedPieceSquare->addPieceWithoutObservers(pieceBack);
        pieceBack->setSquare(killedPieceSquare);
        pieceBack->calculateMoves();
    }

    attackPiece->calculateMoves();
}

//
//
//

Move Computer::generateMove(Board& gameBoard, Colour team, int levels, Colour initialTeam) {
    int level = levels - 1;
    Colour otherTeam = getOtherTeam(team);
    if(team == WHITE) cout << "WHITE TEAM RIGHT NOW" << endl;
    else cout << "BLACK TEAM RIGHT NOW" << endl;

    // Get all of team's moves
    vector<Move> teamMoves = allMoves(team, gameBoard);
    
    int index = 0;

    // Change board locally
    for(Move& m : teamMoves) {
        cout << "Index is currently " << index << " out of " << teamMoves.size() << " moves" << endl;
        if(isValidMove(m)) {
            simulateMove(gameBoard, m, team);
            Piece* attack = attackPiece;
            char killed = killedPiece;
            Square* start = startSquare;
            Square* killedSq = killedPieceSquare;
            Square* attackDest = attackPieceDest;

            if(level == 0) {
                vector<Piece*> initTeamPieces = getAllPieces(initialTeam, gameBoard);
                vector<Piece*> otherTeamPieces = getAllPieces(initialTeam, gameBoard);
                int score = teamValueCalc(gameBoard, initialTeam);
                cout << "Score of this move is " << score << endl;
                m.setValue(score);
            } else {
                m.setValue(generateMove(gameBoard, otherTeam, level, initialTeam).getValue());
            }

            attackPiece = attack;
            killedPiece = killed;
            startSquare = start;
            killedPieceSquare = killedSq;
            attackPieceDest = attackDest;
            undoMove(gameBoard, m, team);
        }
        ++index;
    }    
    if(team != initialTeam) {
        return minOfMoves(teamMoves);
    } else {
        return maxOfMoves(teamMoves);
    }
}

//
//
//

void Computer::makeMove(Board& gameBoard, Colour team) {
    string shouldMove;
    cin >> shouldMove;
    if(shouldMove != "move") return;
        Move ourMove = doMove(gameBoard, team);
            Square* start = &gameBoard.getBoard()[ourMove.getInitX()][ourMove.getInitY()]; 
            Piece* piece = start->getPiece();

            cout << ourMove.getInitX() << ourMove.getInitY() << ourMove.getDestX() << ourMove.getDestY() << endl;
            
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

            if(toupper(piece->getPieceName()) != 'K' && gameBoard.isMate()) {
                dest->removePiece();
                dest->addPiece(opposingPiece);
                start->addPiece(piece);
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
            } else {
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

}
