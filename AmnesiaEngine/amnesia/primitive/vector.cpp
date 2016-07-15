#include "vector.h"

Vector::Vector() : x(0.0), y(0.0) {}

Vector::Vector(Vector &&other) {
  x = other.x;
  y = other.y;
  other.x = 0;
  other.y = 0;
}

Vector::Vector(double x, double y) : x(x), y(y) {}

//============== Static Members =============//
const Vector Vector::up = Vector(0, 1);
const Vector Vector::down = Vector(0, 1);
const Vector Vector::right = Vector(0, 1);
const Vector Vector::left = Vector(0, 1);

//============== Utility =============//
void Vector::set_magnitude(double magnitude) {
  double old_magnitude = this->magnitude();
  double ratio = magnitude / old_magnitude;
  x *= ratio;
  y *= ratio;
}

//============== Operators =============//

std::ostream &operator<<(std::ostream &os, const Vector &vector) {
  return os << "Vector(" << vector.x << ", " << vector.y << ")";
}
