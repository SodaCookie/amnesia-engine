#ifndef _AMNESIA_RECT_HEADER_
#define _AMNESIA_RECT_HEADER_

#include "SDL2/SDL_rect.h"

// Since SDL_Rect is composed of ints
// Rect represents a rectangle of double values
class Rect {

public:
  double x, y, w, h;

  Rect();
  Rect(double x, double y, double w, double h);
  Rect(const SDL_Rect &other);

  bool intersect_rect(const Rect &other);

  SDL_Rect sdl_rect() const;
};

#endif
