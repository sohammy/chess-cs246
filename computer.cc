#include "computer.h"

Computer::Computer() {}


Colour getOtherTeam(Colour c) {
    if(c == WHITE) {
        cout << "Other team is BLACK" << endl;
        return BLACK; 
    }
    cout << "Other team is WHITE" << endl;
    return WHITE;
}


bool isValidMove(Move m) {
    if(m.getDestX() <= 7 && m.getDestX() >= 0 && m.getDestY() <= 7 && m.getDestX() >=0
    && m.getInitX() <= 7 && m.getInitX() >= 0 && m.getInitY() <= 7 && m.getInitY() >=0) return true;
    return false;
}


vector<Piece*> getAllPieces(Colour c, Board& gameBoard) {
    vector<Piece*> pieces;
    if(c == WHITE) {
        for(unsigned int i = 0; i < gameBoard.availableWhites.size() ; ++i) {
            pieces.emplace_back(gameBoard.availableWhites[i].get());
        }
    } else {
        for(unsigned int i = 0; i < gameBoard.availableBlacks.size() ; ++i) {
            pieces.emplace_back(gameBoard.availableBlacks[i].get());
        } 
    }
    return pieces;
}


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


void Computer::simulateMove(Board& gameBoard, Move m, Colour team) {
    attackPiece = nullptr;
    killedPiece = '0';
    startSquare = nullptr;
    killedPieceSquare = nullptr;
    attackPieceDest = nullptr;

    cout << "Trying to make this shit work lol" << endl;

        Square* start = &gameBoard.getBoard()[m.getInitX()][m.getInitY()];
        Piece* piece = start->getPiece();
        // --> cout
        cout << m.getInitX() << m.getInitY() << m.getDestX() << m.getDestY() << endl;
        // --> cout
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
                    // --> cout
                    cout << "Turning on white en passant" << endl; 
                    // --> cout
                    gameBoard.getBoard()[piece->getX() - 1][piece->getY()].turnOnEnPassant();
                } else {
                    // --> cout
                    cout << "Turning on black en passant" << endl;
                    // --> cout
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
            // --> cout
            cout << "We made it into the check check" << endl;
            // --> cout
            dest->removePieceWithoutObservers();
            dest->addPieceWithoutObservers(opposingPiece);
            start->addPieceWithoutObservers(piece);
        } else if(enPassanting) {
            // --> cout
            cout << "It's thinking we en passanting? that seems wrong" << endl;
            // --> cout
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
            // --> cout
            cout << "Trying a normal move, what will happen" << endl;
            // --> cout
            dest->removePieceWithoutObservers();
            dest->addPieceWithoutObservers(opposingPiece);
            if(dest->getPiece() != nullptr) {
                // --> cout
                cout << "Taking a piece now" << endl;
                // --> cout
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


void Computer::undoMove(Board& gameBoard, Move m, Colour team) {
    Piece* pieceBack = nullptr;
    if(killedPiece != '0') {
        unique_ptr<Piece> p = nullptr;
        p = gameBoard.makePiece(killedPiece);
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


Move Computer::generateMove(Board& gameBoard, Colour team, int levels, Colour initialTeam) {
    int level = levels - 1;
    Colour otherTeam = getOtherTeam(team);

    // Get all of team's moves
    vector<Move> teamMoves = allMoves(team, gameBoard);

    cout << teamMoves.size() << endl;
    
    // Change board locally
    int index = 0;
    for(Move m : teamMoves) {
        cout << "Move check number is " << index << endl; 
        if(isValidMove(m)) {
            simulateMove(gameBoard, m, team);

            if(level == 0) {
                vector<Piece*> initTeamPieces = getAllPieces(initialTeam, gameBoard);
                vector<Piece*> otherTeamPieces = getAllPieces(initialTeam, gameBoard);
                int score = teamValueCalc(initTeamPieces) - teamValueCalc(otherTeamPieces);
                m.setValue(score);
                cout << "Score is "<< m.getValue() << endl;
                cout << "Made it past this part here" << endl;
            } else {
                m.setValue(generateMove(gameBoard, otherTeam, level, initialTeam).getValue());
            }
            undoMove(gameBoard, m, team);
            cout << "MADE IT PAST UNDO HERE" << endl;
        }
        ++index;
    }
    
    if(team != initialTeam) {
        return minOfMoves(teamMoves);
    } else {
        return maxOfMoves(teamMoves);
    }
}

void Computer::makeMove(Board& gameBoard, Colour team) {
    string shouldMove;
    cin >> shouldMove;
    if(shouldMove != "move") return;
        Move ourMove = doMove(gameBoard, team);
        if(ourMove.getInitX() < 8 && ourMove.getInitY() < 8 && ourMove.getDestX() < 8 && ourMove.getDestY() < 8) {
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
