#include <iostream>
#include "textdisplay.h"
using namespace std;

TextDisplay::TextDisplay() {

    theDisplay = { {'8', ' ', ' ', '_', ' ', '_', ' ', '_', ' ', '_'},
                   {'7', ' ', '_', ' ', '_', ' ', '_', ' ', '_', ' '},
                   {'6', ' ', ' ', '_', ' ', '_', ' ', '_', ' ', '_'},
                   {'5', ' ', '_', ' ', '_', ' ', '_', ' ', '_', ' '},
                   {'4', ' ', ' ', '_', ' ', '_', ' ', '_', ' ', '_'},
                   {'3', ' ', '_', ' ', '_', ' ', '_', ' ', '_', ' '},
                   {'2', ' ', ' ', '_', ' ', '_', ' ', '_', ' ', '_'},
                   {'1', ' ', '_', ' ', '_', ' ', '_', ' ', '_', ' '},
                   {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                   {' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'},
                 }

}

void TextDisplay::notify(shared_ptr<Square> s) {

    if (s->getPiece() == nullptr) { // When the square does not have a piece on it

      if (s->getX() == 0) {
        theDisplay[s->getY()][s->getX() + 2] = ' ';
      } else {
        theDisplay[s->getY()][s->getX() + 2] = '_';
      }

    } else {

      theDisplay[s->getY()][s->getX() + 2] = s->getPiece()->getpieceName();

    }
    
}

TextDisplay::~TextDisplay() {}


ostream &operator<<(ostream &out, const TextDisplay &td) {
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10; ++j) {
      out << td.theDisplay[i][j];
    }
    out << endl;
  }
  return out;
}
