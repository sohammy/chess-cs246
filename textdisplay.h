#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include "square.h"
#include "piece.h"
#include "observer.h"
using namespace std;
class Square;

class TextDisplay: public Observer {

  vector<vector<char>> theDisplay; 

 public:
  TextDisplay();

  void notify(Square*) override;

  ~TextDisplay();

  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
