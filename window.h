#ifndef WINDOW_H
#define WINDOW_H
#include <X11/Xlib.h>
#include <iostream>
#include <string>

class Xwindow {
  Display *d;
  Window w;
  int s;
  GC gc;
  unsigned long colours[10];

 public:
  Xwindow(int width=500, int height=500);  // Constructor; displays the window.
  ~Xwindow();                              // Destructor; destroys the window.

  enum {White=0, Black, Red, Green, Blue, Purple}; // Available colours.

  // Draws a Rectangle
  void fillRectangle(int x, int y, int width, int height, int colour=Black);

  // Draws a String
  void drawString(int x, int y, std::string msg);

  // Draws a Piece
  void drawPiece(const char* fileName, int xCoord, int yCoord);

};

#endif
