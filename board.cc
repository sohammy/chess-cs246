#include "board.h"

void Board::clearBoard() {
    theBoard.clear();
}

void Board::initializeBoard() {
    clearBoard();
    int boardSize = 8;

    theBoard.resize(boardSize);
    for (int i = 0; i < boardSize; ++i) {
        theBoard[i].resize(boardSize);
    }

    theBoard[0][0] = 'r';
    theBoard[0][1] = 'n';
    theBoard[0][2] = 'b';
    theBoard[0][3] = 'q';
    theBoard[0][4] = 'k';
    theBoard[0][5] = 'b';
    theBoard[0][6] = 'n';
    theBoard[0][7] = 'r';

    for (int i = 0; i < 7; ++i) {
        theBoard[1][i] = 'p';
    }

    theBoard[7][0] = 'R';
    theBoard[7][1] = 'N';
    theBoard[7][2] = 'B';
    theBoard[7][3] = 'Q';
    
    



}