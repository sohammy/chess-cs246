#include "computer.h"

const int SCOREFORFAILEDBRANCHES = -100000;

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


int pawnEncouragementForPromotion(Board& gameBoard, Colour team) {
    int sum = 0;
    vector<Piece*> pieces = getAllPieces(team, gameBoard);
    if(team == WHITE) {
        for(Piece* p : pieces) {
            if(p->getPieceName() == 'P') {
                if(p->getX() < 3) {
                    ++sum;
                }
                if(p->getX() < 1) {
                    sum += 2;
                }
                if(p->getX() == 0) {
                    sum += 7;
                }
            }
        }
    } else {
        for(Piece* p : pieces) {
            if(p->getPieceName() == 'p') {
                if(p->getX() > 4) {
                    ++sum;
                }
                if(p->getX() < 6) {
                    sum += 2;
                }
                if(p->getX() == 7) {
                    sum += 7;
                }
            }
        }
    }
    return sum;
}

int calculateDistanceToCenter(Piece* p) {
    if(abs(3-p->getX()) <= 1 && abs(3-p->getY()) <= 1 && toupper(p->getPieceName()) != 'P') {
        return 5;
    } else if (abs(3-p->getX()) == 2 && abs(3-p->getY()) == 2 && toupper(p->getPieceName()) != 'P') {
        return 3;
    } else if (abs(3-p->getX()) <= 1) {
        return 1;
    } else if (abs(3-p->getY()) <= 1) {
        return 1;
    }
    return 0;
}

int calculatePieceActivityScore( Board& gameBoard, Colour team) {
    int pieceActivityScore = 0;
    for ( auto& row : gameBoard.getBoard()) {
        for ( auto& square : row) {
            if (square.getPiece() != nullptr && square.getPiece()->getColour() == team) {
                int distanceToCenter = calculateDistanceToCenter(square.getPiece());
                pieceActivityScore += distanceToCenter;
            }
        }
    }

    return pieceActivityScore;
}

int calculateMaterialScore(Board& gameBoard, Colour team) {
    int materialBalance = 0;
    for (vector<Square>& vctr : gameBoard.getBoard()) {
        for (Square& square : vctr) {
            if (square.getPiece() != nullptr && square.getPiece()->getColour() == team) {
                materialBalance += getPieceValue(square.getPiece());
            } else if (square.getPiece() != nullptr && square.getPiece()->getColour() != team) {
                materialBalance -= getPieceValue(square.getPiece());
            }
        }
    }
    return materialBalance;
}

int evaluateCurrentPosition(Board& gameBoard, Colour team) {
    int materialScore = calculateMaterialScore(gameBoard, team);
    int pieceAcitivityScore = calculatePieceActivityScore(gameBoard, team);
    int pawnPromotionBonus = pawnEncouragementForPromotion(gameBoard, team);

    int overallEvaluation = materialScore + pieceAcitivityScore + pawnPromotionBonus;

    return overallEvaluation;
}


//
//
//

bool isValidMove(Move m) {
    if(m.getDestX() <= 7 && m.getDestX() >= 0 && m.getDestY() <= 7 && m.getDestY() >=0
    && m.getInitX() <= 7 && m.getInitX() >= 0 && m.getInitY() <= 7 && m.getInitY() >=0) return true;
    return false;
}


// simulateMove(Board, Move, Colour) makes a move behind the scenes and is used to 
// determine the quality of a move, if this function returns false, then we shouldn't
// generate a tree starting from this move
bool Computer::simulateMove(Board& gameBoard, Move m, Colour team) {
    attacker = nullptr;
    defender = nullptr;
    startSquare = nullptr;
    destSquare = nullptr;
    bool foundMove = false;

    startSquare = &gameBoard.getBoard()[m.getInitX()][m.getInitY()];
    attacker = startSquare->getPiece();

    if(attacker != nullptr) {

        if(team == attacker->getColour()) {

            attacker->calculateMoves();

            vector<Move> attackersMoves = attacker->getMoves();
            for(Move move : attackersMoves) {
                if(m.isEqual(move)) {
                    foundMove = true;
                }
            }

            if(foundMove) {
                destSquare = m.getSquare();

                if(destSquare->getPiece() != nullptr) {
                    defender = destSquare->getPiece();
                } else {
                    defender = nullptr;
                }
                
                startSquare->removePieceWithoutObservers();
                destSquare->removePieceWithoutObservers();
                destSquare->addPieceWithoutObservers(attacker);

                // The start of piece checking
                if(toupper(attacker->getPieceName()) != 'K') {
                    // Ensures that this move will not put king in check
                    if(gameBoard.isMate(team)) {
                        destSquare->removePieceWithoutObservers();
                        destSquare->addPieceWithoutObservers(defender);
                        startSquare->addPieceWithoutObservers(attacker);
                        return false;
                    }
                }

                // The piece found a square that it can attack.
                attacker->setSquare(destSquare);
                attacker->pieceMoved();
                attacker->calculateMoves();
                return true;
            }
        }
    }
    return false;
}

// undoMove(Board, Move, Colour) is used to reset the board back to it's initial state, assuming
// that simulate moves was successful
void Computer::undoMove(Board& gameBoard, Move m, Colour team) {
    attacker->pieceUnMoved();
    attacker->setSquare(startSquare);
    destSquare->removePieceWithoutObservers();
    startSquare->removePieceWithoutObservers();
    destSquare->addPieceWithoutObservers(defender);
    startSquare->addPieceWithoutObservers(attacker);
    attacker->calculateMoves();
    if(defender != nullptr) {
        defender->calculateMoves();
    }
}

// generateMove(Board, Colour, int, Colour) is a recursive function that implements the minimax algorithm
// in order to find the best move for a computer player
Move Computer::generateMove(Board& gameBoard, Colour team, int levels, Colour initialTeam, int alpha, int beta) {
    int level = levels - 1;
    Colour otherTeam = getOtherTeam(team);

    // Get all of team's moves
    vector<Move> teamMoves = allMoves(team, gameBoard);
    vector<Move> legalMoves;

    // Change board locally
    for (const Move& m : teamMoves) {
        if (isValidMove(m)) {
            bool possible = simulateMove(gameBoard, m, team);

            if (possible) {
                Square* start = startSquare;
                Square* dest = destSquare;
                Piece* att = attacker;
                Piece* def = defender;

                int moveValue;

                if (level == 0) {
                    moveValue = evaluateCurrentPosition(gameBoard, initialTeam);
                } else {
                    moveValue = generateMove(gameBoard, otherTeam, level, initialTeam, alpha, beta).getValue();
                }

                Move newMove(m, moveValue);
                legalMoves.emplace_back(newMove);

                startSquare = start;
                destSquare = dest;
                attacker = att;
                defender = def;

                undoMove(gameBoard, m, team);

                // Alpha-beta pruning
                if (team != initialTeam) {
                    beta = min(beta, moveValue);
                } else {
                    alpha = max(alpha, moveValue);
                }

                if (beta <= alpha) {
                    break;  // Beta cutoff for minimizing player or alpha cutoff for maximizing player
                }
            }
        }
    }

    if (!legalMoves.empty()) {
        if (team != initialTeam) {
            return minOfMoves(legalMoves);
        } else {
            return maxOfMoves(legalMoves);
        }
    }
    Move noValids = Move(-1,-1,-1,-1,nullptr,N);
    noValids.setValue(SCOREFORFAILEDBRANCHES);
    return noValids;
}

//
//
//

void Computer::makeMove(Board &gameBoard, Colour team) {
    string shouldMove;
    while (cin >> shouldMove) {
        if (shouldMove == "resign") {
            if (team == Colour::BLACK) {
                gameBoard.blackLose = true;
                gameBoard.whiteLose = false;
                return;
            }
            gameBoard.whiteLose = true;
            return;
        }
        if(shouldMove == "move") {
            break;
        }
        cout << "Please enter a valid input" << endl;
    }

    bool foundMove = false;

    while (!foundMove) {
        Move moveAttempted = doMove(gameBoard, team);
        Square *start = &gameBoard.getBoard()[moveAttempted.getInitX()][moveAttempted.getInitY()];
        Piece *piece = start->getPiece();

        if (piece != nullptr) {

            if (team == piece->getColour()) {

                piece->calculateMoves();

                int successIndex = 0;
                vector<Move> possibleMoves = piece->getMoves();
                for (Move m : possibleMoves) {
                    if (moveAttempted.isEqual(m)) {
                        foundMove = true;
                        break;
                    }
                    ++successIndex;
                }

                if (foundMove) { // Once we found move
                    Move successfulMove = possibleMoves[successIndex];
                    Square *dest = successfulMove.getSquare();

                    Piece *opposingPiece = nullptr;
                    if (dest->getPiece() != nullptr) {
                        opposingPiece = dest->getPiece();
                    }

                    start->removePiece();
                    dest->removePiece();
                    dest->addPiece(piece);

                    if (toupper(piece->getPieceName()) != 'K' && gameBoard.isMate()) {
                        dest->removePiece();
                        dest->addPiece(opposingPiece);
                        start->addPiece(piece);
                        foundMove = false;
                    } else {
                        dest->removePiece();
                        dest->addPiece(opposingPiece);
                        if (dest->getPiece() != nullptr) {
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
                } else{
                    cout << "Please make a valid move" << endl;
                }
            } else {
                cout << "You can only select pieces from your team!" << endl;
            }
        } else {
            cout << "Please pick a valid square" << endl;
        }
    }
}
