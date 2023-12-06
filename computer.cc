#include "computer.h"

const int SCOREFORFAILEDBRANCHES = -100000;

Computer::Computer() {}


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


int pointsForDistanceToCenter(Piece* p) {
    // This way we don't just spam pawns in the middle of the board
    if(abs(3-p->getX()) <= 1 && abs(4-p->getY()) <= 1) {
        return 5;
    } else if (abs(3-p->getX()) <= 2 && abs(4-p->getY()) <= 2) {
        return 3;
    } else if (abs(3-p->getX()) <= 1) {
        return 1;
    } else if (abs(4-p->getY()) <= 1) {
        return 1;
    }
    return 0;
}


int bonusForMovingToMiddle( Board& gameBoard, Colour team) {
    int pieceActivityScore = 0;
    for (vector<Square>& vctr : gameBoard.getBoard()) {
        for (Square& square : vctr) {
            if (square.getPiece() != nullptr && square.getPiece()->getColour() == team) {
                int distanceToCenter = pointsForDistanceToCenter(square.getPiece());
                pieceActivityScore += distanceToCenter;
            }
        }
    }

    return pieceActivityScore;
}


int piecesOnBoardValue(Board& gameBoard, Colour team) {
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


int bonusForPuttingKingInCheck(Board& gameBoard, Colour team) {
    Colour other = getOtherTeam(team);
    if(gameBoard.isMate(other)) {
        return 75;
    }
    return 0;
}


int evaluateMove(Board& gameBoard, Colour team) {
    int materialScore = piecesOnBoardValue(gameBoard, team);
    int pieceAcitivityScore = bonusForMovingToMiddle(gameBoard, team);
    int pawnPromotionBonus = pawnEncouragementForPromotion(gameBoard, team);
    int bonusForOtherKingInCheck = bonusForPuttingKingInCheck(gameBoard, team);

    int overallEvaluation = materialScore + pieceAcitivityScore + pawnPromotionBonus + bonusForOtherKingInCheck;

    return overallEvaluation;
}


bool isValidMove(Move m) {
    if(m.getDestX() <= 7 && m.getDestX() >= 0 && m.getDestY() <= 7 && m.getDestY() >=0
    && m.getInitX() <= 7 && m.getInitX() >= 0 && m.getInitY() <= 7 && m.getInitY() >=0) return true;
    return false;
}


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
                    moveValue = evaluateMove(gameBoard, initialTeam);
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
        cout << "Loading move..." << endl;
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
                    dest->addPieceWithoutObservers(piece);

                    if (toupper(piece->getPieceName()) != 'K' && gameBoard.isMate(team)) {
                        dest->removePiece();
                        dest->addPiece(opposingPiece);
                        start->addPiece(piece);
                        foundMove = false;
                    } else {
                        dest->removePieceWithoutObservers();
                        dest->addPieceWithoutObservers(opposingPiece);
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
