#include "rect.h"

Rect::Rect() {}

Rect::Rect(double x, double y, double w, double h) : x(x), y(y), w(w), h(h) {}

Rect::Rect(const SDL_Rect &other) {
  x = other.x;
  y = other.y;
  w = other.w;
  h = other.h;
}

bool Rect::intersect_rect(const Rect &other) {
  return !(other.x > x + w || other.x + other.w < x || other.y > y + h ||
           other.y + other.h < y);
}

SDL_Rect Rect::sdl_rect() const {
  SDL_Rect rect;
  rect.x = x;
  rect.y = y;
  rect.w = w;
  rect.h = h;
  return rect;
}
