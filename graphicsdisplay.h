#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H
#include <iostream>
#include <vector>
#include "observer.h"
#include "window.h"
#include "piece.h"
class Square;

class GraphicsDisplay: public Observer {
  Xwindow myWindow{800, 800};
  const int gridSize;
 public:
  GraphicsDisplay(int n);

  void notify(Square* s) override;

  ~GraphicsDisplay();
};

#endif
