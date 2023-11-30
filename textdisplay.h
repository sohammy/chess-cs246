#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include "square.h"
#include "observer.h"
using namespace std;
class Square;

class TextDisplay: public Observer {

  vector<vector<char>> theDisplay; 

 public:
  TextDisplay();

  void notify(shared_ptr<Square>) override;

  ~TextDisplay();

  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
