#include "piece.h"

void Piece::setColour(char c) {
    if (c == 'w') pieceColour = WHITE;
    if (c == 'b') pieceColour = BLACK;
}

void Piece::movesInDir(Direction d) {
    int x = position->getX();
    int y = position->getY();
    if (d == N) {
        while(y > 0) {
            --y;
            
        }
    } else if (d == E) {

    } else if (d == S) {

    } else if (d == W) {

    } else if (d == NE) {

    } else if (d == NW) {

    } else if (d == SE) {

    } else if (d == SW) {

    }
}

void Piece::notify(Square& s) {
    bool isInPossibleMoves = true;
    Direction d;
    for(Move m : blockedMoves) {
        if(m.getSquare() == &s) {
            d = m.getDirection();
            isInPossibleMoves = false; 
            break; 
        }
    }

    if(isInPossibleMoves) {
        for(Move m : possibleMoves) {
            if(m.getSquare() == &s) {
                d = m.getDirection();
                break;
            }
        }
    }

    if(isInPossibleMoves) {
        if(d == N) {
            for (int i = 0; i < possibleMoves.size(); ++i) {
                if(possibleMoves[i].getDirection() == N 
                && possibleMoves[i].getDestY() <= s.getY()) {
                    possibleMoves[i].getSquare()->removePieceObserver(this);
                    possibleMoves.erase(possibleMoves.begin() + i);
                }
            }
            for (int i = 0; i < blockedMoves.size(); ++i) {
                if(blockedMoves[i].getDirection() == N 
                && blockedMoves[i].getDestY() <= s.getY()) {
                    blockedMoves[i].getSquare()->removePieceObserver(this);
                    blockedMoves.erase(blockedMoves.begin() + i);
                }
            }
        } else if (d == E) {
           for (int i = 0; i < possibleMoves.size(); ++i) {
                if(possibleMoves[i].getDirection() == E 
                && possibleMoves[i].getDestX() >= s.getX()) {
                    possibleMoves[i].getSquare()->removePieceObserver(this);
                    possibleMoves.erase(possibleMoves.begin() + i);
                }
            }
            for (int i = 0; i < blockedMoves.size(); ++i) {
                if(blockedMoves[i].getDirection() == E 
                && blockedMoves[i].getDestX() >= s.getX()) {
                    blockedMoves[i].getSquare()->removePieceObserver(this);
                    blockedMoves.erase(blockedMoves.begin() + i);
                }
            } 
        } else if (d == S) {
            for (int i = 0; i < possibleMoves.size(); ++i) {
                if(possibleMoves[i].getDirection() == S 
                && possibleMoves[i].getDestY() >= s.getY()) {
                    possibleMoves[i].getSquare()->removePieceObserver(this);
                    possibleMoves.erase(possibleMoves.begin() + i);
                }
            }
            for (int i = 0; i < blockedMoves.size(); ++i) {
                if(blockedMoves[i].getDirection() == S 
                && blockedMoves[i].getDestY() >= s.getY()) {
                    blockedMoves[i].getSquare()->removePieceObserver(this);
                    blockedMoves.erase(blockedMoves.begin() + i);
                }
            }
        } else if (d == W) {
            for (int i = 0; i < possibleMoves.size(); ++i) {
                if(possibleMoves[i].getDirection() == W 
                && possibleMoves[i].getDestX() <= s.getX()) {
                    possibleMoves[i].getSquare()->removePieceObserver(this);
                    possibleMoves.erase(possibleMoves.begin() + i);
                }
            }
            for (int i = 0; i < blockedMoves.size(); ++i) {
                if(blockedMoves[i].getDirection() == W 
                && blockedMoves[i].getDestX() <= s.getX()) {
                    blockedMoves[i].getSquare()->removePieceObserver(this);
                    blockedMoves.erase(blockedMoves.begin() + i);
                }
            }
        } else if (d == NE) {
            for (int i = 0; i < possibleMoves.size(); ++i) {
                if(possibleMoves[i].getDirection() == NE 
                && possibleMoves[i].getDestY() <= s.getY()
                && possibleMoves[i].getDestX() >= s.getX()) {
                    possibleMoves[i].getSquare()->removePieceObserver(this);
                    possibleMoves.erase(possibleMoves.begin() + i);
                }
            }
            for (int i = 0; i < blockedMoves.size(); ++i) {
                if(blockedMoves[i].getDirection() == NE 
                && blockedMoves[i].getDestY() <= s.getY()
                && blockedMoves[i].getDestX() >= s.getX()) {
                    blockedMoves[i].getSquare()->removePieceObserver(this);
                    blockedMoves.erase(blockedMoves.begin() + i);
                }
            }
        } else if (d == NW) {
            for (int i = 0; i < possibleMoves.size(); ++i) {
                if(possibleMoves[i].getDirection() == NW 
                && possibleMoves[i].getDestY() <= s.getY()
                && possibleMoves[i].getDestX() <= s.getX()) {
                    possibleMoves[i].getSquare()->removePieceObserver(this);
                    possibleMoves.erase(possibleMoves.begin() + i);
                }
            }
            for (int i = 0; i < blockedMoves.size(); ++i) {
                if(blockedMoves[i].getDirection() == NW 
                && blockedMoves[i].getDestY() <= s.getY()
                && blockedMoves[i].getDestX() <= s.getX()) {
                    blockedMoves[i].getSquare()->removePieceObserver(this);
                    blockedMoves.erase(blockedMoves.begin() + i);
                }
            }
        } else if (d == SE) {
            for (int i = 0; i < possibleMoves.size(); ++i) {
                if(possibleMoves[i].getDirection() == SE 
                && possibleMoves[i].getDestY() >= s.getY()
                && possibleMoves[i].getDestX() >= s.getX()) {
                    possibleMoves[i].getSquare()->removePieceObserver(this);
                    possibleMoves.erase(possibleMoves.begin() + i);
                }
            }
            for (int i = 0; i < blockedMoves.size(); ++i) {
                if(blockedMoves[i].getDirection() == SE 
                && blockedMoves[i].getDestY() >= s.getY()
                && blockedMoves[i].getDestX() >= s.getX()) {
                    blockedMoves[i].getSquare()->removePieceObserver(this);
                    blockedMoves.erase(blockedMoves.begin() + i);
                }
            }
        } else if (d == SW) {
            for (int i = 0; i < possibleMoves.size(); ++i) {
                if(possibleMoves[i].getDirection() == SW 
                && possibleMoves[i].getDestY() >= s.getY()
                && possibleMoves[i].getDestX() <= s.getX()) {
                    possibleMoves[i].getSquare()->removePieceObserver(this);
                    possibleMoves.erase(possibleMoves.begin() + i);
                }
            }
            for (int i = 0; i < blockedMoves.size(); ++i) {
                if(blockedMoves[i].getDirection() == SW 
                && blockedMoves[i].getDestY() >= s.getY()
                && blockedMoves[i].getDestX() <= s.getX()) {
                    blockedMoves[i].getSquare()->removePieceObserver(this);
                    blockedMoves.erase(blockedMoves.begin() + i);
                }
            }
        }

        Move newMove = Move{position->getX(), position->getY(), s.getX(), s.getY(), d, &s};

        if(pieceName != 'P') {
            if(pieceColour != s.getPiece()->getColour()) {
                 possibleMoves.emplace_back(newMove);
            } else {
                blockedMoves.emplace_back(newMove);
            }
        } else {
            blockedMoves.emplace_back(newMove);
        }
        s.addPieceObservers(this);

    } else {
        if(s.getPiece() != nullptr && s.getPiece()->getColour() != pieceColour) {
            if(d == N) {
                
            } else if (d == E) {

            } else if (d == S) {

            } else if (d == W) {

            } else if (d == NE) {

            } else if (d == NW) {

            } else if (d == SE) {

            } else if (d == SW) {

            }
        }
    }

}
