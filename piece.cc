#include "piece.h"
#include "king.h"

Piece::Piece(vector<vector<Square>>& board, char pieceName) : theBoard{board}, pieceName{pieceName} {}

void Piece::setColour(char c) {
    if (c == 'w') pieceColour = WHITE;
    if (c == 'b') pieceColour = BLACK;
}

void Piece::setPieceName(char c) {
    pieceName = c;
}

void Piece::setSquare(Square* s) {
    position = s;
}

vector<Piece*> Piece::getTeamOfColour(Colour c) {
    vector<Piece*> pieces;
    for(unsigned int i = 0; i < theBoard.size(); ++i) {
        for(unsigned int j = 0; j < theBoard.size(); ++j) {
            if(theBoard[i][j].getPiece() != nullptr) {
                if(theBoard[i][j].getPiece()->getColour() == c) {
                    pieces.emplace_back(theBoard[i][j].getPiece());
                }
            }
        }
    }
    return pieces;
}

vector<Move> Piece::getTeamsMoves(Colour c) {
    vector<Piece*> pieces = getTeamOfColour(c);
    vector<Move> allMoves;
    for(Piece* p : pieces) {
        vector<Move> thisPiecesMoves;
        if(toupper(p->getPieceName()) == 'K') {
            King* king = dynamic_cast<King*>(p);
            thisPiecesMoves = king->movesIncludingNonLegal(king->getX(), king->getY());
        } else {
            p->calculateMoves();
            thisPiecesMoves = p->getMoves();
        }
        for(Move m : thisPiecesMoves) {
            allMoves.emplace_back(m);
        }
    }
    return allMoves;
}

vector<Move> Piece::getTeamsBlockedMoves(Colour c) {
    vector<Piece*> pieces = getTeamOfColour(c);
    vector<Move> allMoves;
    for(Piece* p : pieces) {
        vector<Move> thisPiecesMoves;
        thisPiecesMoves = p->getBlockedMoves();

        for(Move m : thisPiecesMoves) {
            allMoves.emplace_back(m);
        }
    } 
    return allMoves;
}

// MOVESINDIR FUNCTION //

void Piece::movesInDir(Direction d, int n) {
    int x = position->getX();
    int y = position->getY();
    if (d == W) {
        while(y > 0 && n >= 1) {
            --n;
            --y;
            Move m = Move(position->getX(), position->getY(), x, y, &theBoard[x][y], d);
            if(theBoard[x][y].getPiece() == nullptr) {
                possibleMoves.emplace_back(m);
                theBoard[x][y].addPieceObservers(this);
            } else if (theBoard[x][y].getPiece()->getColour() == pieceColour) {
                blockedMoves.emplace_back(m);
                theBoard[x][y].addPieceObservers(this);
                break;
            } else {
                possibleMoves.emplace_back(m);
                theBoard[x][y].addPieceObservers(this);
                if(n != 0) {
                    if(y > 0 && theBoard[x][y].getPiece() != nullptr && toupper(theBoard[x][y].getPiece()->getPieceName()) == 'K') {
                        Move n = Move(position->getX(), position->getY(), x, y - 1, &theBoard[x][y-1], d);
                        blockedMoves.emplace_back(n);
                    }
                }
                break;
            }
        }
    } else if (d == S) {
        while(x < 7 && n >= 1) {
            --n;
            ++x;
            Move m = Move(position->getX(), position->getY(), x, y, &theBoard[x][y], d);
            if(theBoard[x][y].getPiece() == nullptr) {
                possibleMoves.emplace_back(m);
                theBoard[x][y].addPieceObservers(this);
            } else if (theBoard[x][y].getPiece()->getColour() == pieceColour) {
                blockedMoves.emplace_back(m);
                theBoard[x][y].addPieceObservers(this);
                break;
            } else {
                possibleMoves.emplace_back(m);
                theBoard[x][y].addPieceObservers(this);
                if(n != 0) {
                    if(x < 7 && theBoard[x][y].getPiece() != nullptr && toupper(theBoard[x][y].getPiece()->getPieceName()) == 'K') {
                        Move n = Move(position->getX(), position->getY(), x + 1, y, &theBoard[x + 1][y], d);
                        blockedMoves.emplace_back(n);
                    }
                }
                break;
            }
        }
    } else if (d == E) {
        while(y < 7 && n >= 1) {
            --n;
            ++y;
            Move m = Move(position->getX(), position->getY(), x, y, &theBoard[x][y], d);
            if(theBoard[x][y].getPiece() == nullptr) {
                possibleMoves.emplace_back(m);
                theBoard[x][y].addPieceObservers(this);
            } else if (theBoard[x][y].getPiece()->getColour() == pieceColour) {
                blockedMoves.emplace_back(m);
                theBoard[x][y].addPieceObservers(this);
                break;
            } else {
                possibleMoves.emplace_back(m);
                theBoard[x][y].addPieceObservers(this);
                if(n != 0) {
                    if(y < 7 && theBoard[x][y].getPiece() != nullptr && toupper(theBoard[x][y].getPiece()->getPieceName()) == 'K') {
                        Move n = Move(position->getX(), position->getY(), x, y + 1, &theBoard[x][y + 1], d);
                        blockedMoves.emplace_back(n);
                    }
                }
                break;
            }
        }
    } else if (d == N) {
        while(x > 0 && n >= 1) {
            --n;
            --x;
            Move m = Move(position->getX(), position->getY(), x, y, &theBoard[x][y], d);
            if(theBoard[x][y].getPiece() == nullptr) {
                possibleMoves.emplace_back(m);
                theBoard[x][y].addPieceObservers(this);
            } else if (theBoard[x][y].getPiece()->getColour() == pieceColour) {
                blockedMoves.emplace_back(m);
                theBoard[x][y].addPieceObservers(this);
                break;
            } else {
                possibleMoves.emplace_back(m);
                theBoard[x][y].addPieceObservers(this);
                if(n != 0) {
                    if(x > 0 && theBoard[x][y].getPiece() != nullptr && toupper(theBoard[x][y].getPiece()->getPieceName()) == 'K') {
                        Move n = Move(position->getX(), position->getY(), x - 1, y, &theBoard[x - 1][y], d);
                        blockedMoves.emplace_back(n);
                    }
                }
                break;
            }
        }
    } else if (d == SW) {
        while(y > 0 && x < 7 && n >= 1) {
            --n;
            --y;
            ++x;
            Move m = Move(position->getX(), position->getY(), x, y, &theBoard[x][y], d);
            if(theBoard[x][y].getPiece() == nullptr) {
                possibleMoves.emplace_back(m);
                theBoard[x][y].addPieceObservers(this);
            } else if (theBoard[x][y].getPiece()->getColour() == pieceColour) {
                blockedMoves.emplace_back(m);
                theBoard[x][y].addPieceObservers(this);
                break;
            } else {
                possibleMoves.emplace_back(m);
                theBoard[x][y].addPieceObservers(this);
                if(n != 0) {
                    if(y > 0 && x < 7 && theBoard[x][y].getPiece() != nullptr && toupper(theBoard[x][y].getPiece()->getPieceName()) == 'K') {
                        Move n = Move(position->getX(), position->getY(), x + 1, y - 1, &theBoard[x + 1][y - 1], d);
                        blockedMoves.emplace_back(n);
                    }
                }
                break;
            }
        }
    } else if (d == NW) {
        while(y > 0 && x > 0 && n >= 1) {
            --n;
            --y;
            --x;
            Move m = Move(position->getX(), position->getY(), x, y, &theBoard[x][y], d);
            if(theBoard[x][y].getPiece() == nullptr) {
                possibleMoves.emplace_back(m);
                theBoard[x][y].addPieceObservers(this);
            } else if (theBoard[x][y].getPiece()->getColour() == pieceColour) {
                blockedMoves.emplace_back(m);
                theBoard[x][y].addPieceObservers(this);
                break;
            } else {
                possibleMoves.emplace_back(m);
                theBoard[x][y].addPieceObservers(this);
                if(n != 0) {
                    if(y > 0 && x > 0 && theBoard[x][y].getPiece() != nullptr && toupper(theBoard[x][y].getPiece()->getPieceName()) == 'K') {
                        Move n = Move(position->getX(), position->getY(), x - 1, y - 1, &theBoard[x - 1][y - 1], d);
                        blockedMoves.emplace_back(n);
                    }
                }
                break;
            }
        }
    } else if (d == SE) {
        while(y < 7 && x < 7 && n >= 1) {
            --n;
            ++y;
            ++x;
            Move m = Move(position->getX(), position->getY(), x, y, &theBoard[x][y], d);
            if(theBoard[x][y].getPiece() == nullptr) {
                possibleMoves.emplace_back(m);
                theBoard[x][y].addPieceObservers(this);
            } else if (theBoard[x][y].getPiece()->getColour() == pieceColour) {
                blockedMoves.emplace_back(m);
                theBoard[x][y].addPieceObservers(this);
                break;
            } else {
                possibleMoves.emplace_back(m);
                theBoard[x][y].addPieceObservers(this);
                if(n != 0) {
                    if(y < 7 && x < 7 && theBoard[x][y].getPiece() != nullptr && toupper(theBoard[x][y].getPiece()->getPieceName()) == 'K') {
                        Move n = Move(position->getX(), position->getY(), x + 1, y + 1, &theBoard[x + 1][y + 1], d);
                        blockedMoves.emplace_back(n);
                    }
                }
                break;
            }
        }
    } else if (d == NE) {
        while(y < 7 && x > 0 && n >= 1) {
            --n;
            ++y;
            --x;
            Move m = Move(position->getX(), position->getY(), x, y, &theBoard[x][y], d);
            if(theBoard[x][y].getPiece() == nullptr) {
                possibleMoves.emplace_back(m);
                theBoard[x][y].addPieceObservers(this);
            } else if (theBoard[x][y].getPiece()->getColour() == pieceColour) {
                blockedMoves.emplace_back(m);
                theBoard[x][y].addPieceObservers(this);
                break;
            } else {
                possibleMoves.emplace_back(m);
                theBoard[x][y].addPieceObservers(this);
                if(n != 0) {
                    if(y < 7 && x > 0 && theBoard[x][y].getPiece() != nullptr && toupper(theBoard[x][y].getPiece()->getPieceName()) == 'K') {
                        Move n = Move(position->getX(), position->getY(), x - 1, y + 1, &theBoard[x - 1][y + 1], d);
                        blockedMoves.emplace_back(n);
                    }
                }
                break;
            }
        }
    }
}

// NOTIFY FUNCTION //

void Piece::notify(Square* s) {
    bool isInPossibleMoves = true;
    Direction d;
    for(Move m : blockedMoves) {
        if(m.getSquare() == s) {
            d = m.getDirection();
            isInPossibleMoves = false; 
            break; 
        }
    }

    if(isInPossibleMoves) {
        for(Move m : possibleMoves) {
            if(m.getSquare() == s) {
                d = m.getDirection();
                break;
            }
        }
    }

    if(isInPossibleMoves) {
        if(d == N) {
            for (unsigned int i = 0; i < possibleMoves.size(); ++i) {
                if(possibleMoves[i].getDirection() == N 
                && possibleMoves[i].getDestY() <= s->getY()) {
                    possibleMoves[i].getSquare()->removePieceObserver(this);
                    possibleMoves.erase(possibleMoves.begin() + i);
                }
            }
            for (unsigned int i = 0; i < blockedMoves.size(); ++i) {
                if(blockedMoves[i].getDirection() == N 
                && blockedMoves[i].getDestY() <= s->getY()) {
                    blockedMoves[i].getSquare()->removePieceObserver(this);
                    blockedMoves.erase(blockedMoves.begin() + i);
                }
            }
        } else if (d == E) {
           for (unsigned int i = 0; i < possibleMoves.size(); ++i) {
                if(possibleMoves[i].getDirection() == E 
                && possibleMoves[i].getDestX() >= s->getX()) {
                    possibleMoves[i].getSquare()->removePieceObserver(this);
                    possibleMoves.erase(possibleMoves.begin() + i);
                }
            }
            for (unsigned int i = 0; i < blockedMoves.size(); ++i) {
                if(blockedMoves[i].getDirection() == E 
                && blockedMoves[i].getDestX() >= s->getX()) {
                    blockedMoves[i].getSquare()->removePieceObserver(this);
                    blockedMoves.erase(blockedMoves.begin() + i);
                }
            } 
        } else if (d == S) {
            for (unsigned int i = 0; i < possibleMoves.size(); ++i) {
                if(possibleMoves[i].getDirection() == S 
                && possibleMoves[i].getDestY() >= s->getY()) {
                    possibleMoves[i].getSquare()->removePieceObserver(this);
                    possibleMoves.erase(possibleMoves.begin() + i);
                }
            }
            for (unsigned int i = 0; i < blockedMoves.size(); ++i) {
                if(blockedMoves[i].getDirection() == S 
                && blockedMoves[i].getDestY() >= s->getY()) {
                    blockedMoves[i].getSquare()->removePieceObserver(this);
                    blockedMoves.erase(blockedMoves.begin() + i);
                }
            }
        } else if (d == W) {
            for (unsigned int i = 0; i < possibleMoves.size(); ++i) {
                if(possibleMoves[i].getDirection() == W 
                && possibleMoves[i].getDestX() <= s->getX()) {
                    possibleMoves[i].getSquare()->removePieceObserver(this);
                    possibleMoves.erase(possibleMoves.begin() + i);
                }
            }
            for (unsigned int i = 0; i < blockedMoves.size(); ++i) {
                if(blockedMoves[i].getDirection() == W 
                && blockedMoves[i].getDestX() <= s->getX()) {
                    blockedMoves[i].getSquare()->removePieceObserver(this);
                    blockedMoves.erase(blockedMoves.begin() + i);
                }
            }
        } else if (d == NE) {
            for (unsigned int i = 0; i < possibleMoves.size(); ++i) {
                if(possibleMoves[i].getDirection() == NE 
                && possibleMoves[i].getDestY() <= s->getY()
                && possibleMoves[i].getDestX() >= s->getX()) {
                    possibleMoves[i].getSquare()->removePieceObserver(this);
                    possibleMoves.erase(possibleMoves.begin() + i);
                }
            }
            for (unsigned int i = 0; i < blockedMoves.size(); ++i) {
                if(blockedMoves[i].getDirection() == NE 
                && blockedMoves[i].getDestY() <= s->getY()
                && blockedMoves[i].getDestX() >= s->getX()) {
                    blockedMoves[i].getSquare()->removePieceObserver(this);
                    blockedMoves.erase(blockedMoves.begin() + i);
                }
            }
        } else if (d == NW) {
            for (unsigned int i = 0; i < possibleMoves.size(); ++i) {
                if(possibleMoves[i].getDirection() == NW 
                && possibleMoves[i].getDestY() <= s->getY()
                && possibleMoves[i].getDestX() <= s->getX()) {
                    possibleMoves[i].getSquare()->removePieceObserver(this);
                    possibleMoves.erase(possibleMoves.begin() + i);
                }
            }
            for (unsigned int i = 0; i < blockedMoves.size(); ++i) {
                if(blockedMoves[i].getDirection() == NW 
                && blockedMoves[i].getDestY() <= s->getY()
                && blockedMoves[i].getDestX() <= s->getX()) {
                    blockedMoves[i].getSquare()->removePieceObserver(this);
                    blockedMoves.erase(blockedMoves.begin() + i);
                }
            }
        } else if (d == SE) {
            for (unsigned int i = 0; i < possibleMoves.size(); ++i) {
                if(possibleMoves[i].getDirection() == SE 
                && possibleMoves[i].getDestY() >= s->getY()
                && possibleMoves[i].getDestX() >= s->getX()) {
                    possibleMoves[i].getSquare()->removePieceObserver(this);
                    possibleMoves.erase(possibleMoves.begin() + i);
                }
            }
            for (unsigned int i = 0; i < blockedMoves.size(); ++i) {
                if(blockedMoves[i].getDirection() == SE 
                && blockedMoves[i].getDestY() >= s->getY()
                && blockedMoves[i].getDestX() >= s->getX()) {
                    blockedMoves[i].getSquare()->removePieceObserver(this);
                    blockedMoves.erase(blockedMoves.begin() + i);
                }
            }
        } else if (d == SW) {
            for (unsigned int i = 0; i < possibleMoves.size(); ++i) {
                if(possibleMoves[i].getDirection() == SW 
                && possibleMoves[i].getDestY() >= s->getY()
                && possibleMoves[i].getDestX() <= s->getX()) {
                    possibleMoves[i].getSquare()->removePieceObserver(this);
                    possibleMoves.erase(possibleMoves.begin() + i);
                }
            }
            for (unsigned int i = 0; i < blockedMoves.size(); ++i) {
                if(blockedMoves[i].getDirection() == SW 
                && blockedMoves[i].getDestY() >= s->getY()
                && blockedMoves[i].getDestX() <= s->getX()) {
                    blockedMoves[i].getSquare()->removePieceObserver(this);
                    blockedMoves.erase(blockedMoves.begin() + i);
                }
            }
        }

        Move newMove = Move{position->getX(), position->getY(), s->getX(), s->getY(), s, d};

        if(pieceName != 'P' || pieceName != 'p') {
            if(pieceColour != s->getPiece()->getColour()) {
                 possibleMoves.emplace_back(newMove);
            } else {
                blockedMoves.emplace_back(newMove);
            }
        } else {
            blockedMoves.emplace_back(newMove);
        }
        s->addPieceObservers(this);

    } else {
        if(pieceName == 'p' || pieceName == 'P') calculateMoves();
        else if(pieceName == 'n' || pieceName == 'N') calculateMoves();
        else if(pieceName == 'k' || pieceName == 'K') calculateMoves();
        else if(s->getPiece() != nullptr && s->getPiece()->getColour() != pieceColour) {
            if(d == N) {
                for(unsigned int i = 0; i < possibleMoves.size(); ++i) {
                    if (possibleMoves[i].getDirection() == N) {
                        possibleMoves.erase(possibleMoves.begin() + i); 
                    }
                }
                movesInDir(N);
            } else if (d == E) {
                for(unsigned int i = 0; i < possibleMoves.size(); ++i) {
                    if (possibleMoves[i].getDirection() == E) {
                        possibleMoves.erase(possibleMoves.begin() + i); 
                    }
                }
                movesInDir(E); 
            } else if (d == S) {
                for(unsigned int i = 0; i < possibleMoves.size(); ++i) {
                    if (possibleMoves[i].getDirection() == S) {
                        possibleMoves.erase(possibleMoves.begin() + i); 
                    }
                }
                movesInDir(S);
            } else if (d == W) {
                for(unsigned int i = 0; i < possibleMoves.size(); ++i) {
                    if (possibleMoves[i].getDirection() == W) {
                        possibleMoves.erase(possibleMoves.begin() + i); 
                    }
                }
                movesInDir(W);
            } else if (d == NE) {
                for(unsigned int i = 0; i < possibleMoves.size(); ++i) {
                    if (possibleMoves[i].getDirection() == NE) {
                        possibleMoves.erase(possibleMoves.begin() + i); 
                    }
                }
                movesInDir(NE);
            } else if (d == NW) {
                for(unsigned int i = 0; i < possibleMoves.size(); ++i) {
                    if (possibleMoves[i].getDirection() == NW) {
                        possibleMoves.erase(possibleMoves.begin() + i); 
                    }
                }
                movesInDir(NW);
            } else if (d == SE) {
                for(unsigned int i = 0; i < possibleMoves.size(); ++i) {
                    if (possibleMoves[i].getDirection() == SE) {
                        possibleMoves.erase(possibleMoves.begin() + i); 
                    }
                }
                movesInDir(SE);
            } else if (d == SW) {
                for(unsigned int i = 0; i < possibleMoves.size(); ++i) {
                    if (possibleMoves[i].getDirection() == SW) {
                        possibleMoves.erase(possibleMoves.begin() + i); 
                    }
                }
                movesInDir(SW);
            }
        }
    }
}
