#include <iostream>
#include "textdisplay.h"
#include "cell.h"
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

void TextDisplay::notify(Cell &c) {

    if (c.getPiece == nullptr) {
        if (c.getX()%2 == 0) {
          theDisplay[]
        }
    }
    
}

TextDisplay::~TextDisplay() {
  for (int i = 0; i < theDisplay.size(); ++i) {
    theDisplay[i].clear();
  }
  theDisplay.clear();
}

ostream &operator<<(ostream &out, const TextDisplay &td) {
  for (int i = 0; i < td.gridSize; ++i) {
    for (int j = 0; j < td.gridSize; ++j) {
      out << td.theDisplay[i][j];
    }
    out << endl;
  }
  return out;
}
