#include <iostream>
#include "graphicsdisplay.h"
#include "square.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay(int n) : gridSize(n) {
  int size = 800/gridSize;
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      if ((i + j)%2 == 0) {
        myWindow.drawPiece("pieces/Dark_Background.png", i * size, j * size);
      } else {
        myWindow.drawPiece("pieces/Light_Background.png", i * size, j * size);
      }
    }
  }
}

void GraphicsDisplay::notify(Square* s) {
  const int LEN = 100;
  string dir = "pieces/";

  if (s->getPiece() != nullptr) {
      if (s->getPiece()->getPieceName() == 'K') {
      dir += "K-";
    } else if (s->getPiece()->getPieceName() == 'Q') {
      dir += "Q-";
    } else if (s->getPiece()->getPieceName() == 'R') {
      dir += "R-";
    } else if (s->getPiece()->getPieceName() == 'N') {
      dir += "N-";
    } else if (s->getPiece()->getPieceName() == 'B') {
      dir += "B-";
    } else if (s->getPiece()->getPieceName() == 'P') {
      dir += "P-";
    } else if (s->getPiece()->getPieceName() == 'k') {
      dir += "BLACKk-";
    } else if (s->getPiece()->getPieceName() == 'q') {
      dir += "BLACKq-";
    } else if (s->getPiece()->getPieceName() == 'r') {
      dir += "BLACKr-";
    } else if (s->getPiece()->getPieceName() == 'n') {
      dir += "BLACKn-";
    } else if (s->getPiece()->getPieceName() == 'b') {
      dir += "BLACKb-";
    } else if (s->getPiece()->getPieceName() == 'p') {
      dir += "BLACKp-";
    }
  }

    if ((s->getX() + s->getY())%2 == 0) {
      dir += "Dark_Background.png";
    } else {
      dir += "Light_Background.png";
    }

    const char* dirC = dir.c_str();
    myWindow.drawPiece(dirC, s->getY() * LEN, s->getX() * LEN);
    
}

GraphicsDisplay::~GraphicsDisplay() {}
