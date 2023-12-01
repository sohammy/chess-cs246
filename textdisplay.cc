#include <iostream>
#include "textdisplay.h"
using namespace std;

TextDisplay::TextDisplay() {
  theDisplay.clear();
  vector<char> firstRow = {'8','7','6','5','4','3','2','1',' ',' '};
  vector<char> secondRow = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
  vector<char> endings = {' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
  for(int i = 0; i < 10; ++i) {
    vector<char> newVec;
    newVec.clear();
    if(i == 0) {
      theDisplay.emplace_back(firstRow);
    } else if (i == 1) {
      theDisplay.emplace_back(secondRow);
    } else {
      if(i % 2 == 0) {
        newVec = {' ', '_', ' ', '_', ' ', '_', ' ', '_', ' '};
      } else {
        newVec = {'_',' ', '_', ' ', '_', ' ', '_', ' ', ' '};
      }
      newVec.emplace_back(endings[i]);
      theDisplay.emplace_back(newVec);
    }
  }
} 

void TextDisplay::notify(Square* s) {
    int x = s->getX();
    int y = s->getY();
    if (s->getPiece() != nullptr) { // When the square does not have a piece on it
        char c = s->getPiece()->getPieceName();
        theDisplay[y + 2][x] = c;
    } else {
        char newChar;
        if(x % 2 == 0) {
            if(y % 2 == 0) {
                newChar = ' ';
            } else {
                newChar = '_';
            }
        } else {
            if(y % 2 == 0) {
                newChar = '_';
            } else {
                newChar = ' ';
            }
        }
        theDisplay[y + 2][x] = newChar;
    } 
}

TextDisplay::~TextDisplay() {}


ostream &operator<<(ostream &out, const TextDisplay &td) {

  out << "---------- CURRENT BOARD ----------" << endl;
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10; ++j) {
      out << td.theDisplay[j][i];
    }
    out << endl;
  }
  out << "====================================" << endl;
  out << endl;
  return out;
}
