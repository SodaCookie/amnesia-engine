#ifndef _AMNESIA_VECTOR_HEADER_
#define _AMNESIA_VECTOR_HEADER_

#include <cmath>
#include <ostream>

class Vector {

public:
  double x, y;
  const static Vector up;
  const static Vector down;
  const static Vector right;
  const static Vector left;

  Vector();
  Vector(Vector &&other);
  Vector(const Vector &other) = default;
  Vector &operator=(const Vector &other) = default;
  Vector(double x, double y);
  ~Vector() = default;

  inline double magnitude() const { return std::sqrt(x * x + y * y); }

  inline double angle(const Vector &reference) const {
    return std::atan2(y, x) - std::atan2(reference.y, reference.x);
  }

  inline double dot(const Vector &other) const { return other.x + y * other.y; }

  inline double cross(const Vector &other) const {
    return x * other.y - y * other.x;
  }

  inline Vector rotate(double angle) const {
    double new_x = cos(angle) * x - sin(angle) * y;
    double new_y = sin(angle) * x + cos(angle) * y;
    return Vector(new_x, new_y);
  }

  inline bool parallel(const Vector &other) const {
    const double epsilon = 0.00001;
    return cross(other) < epsilon;
  }

  inline Vector normalized() const {
    double magnitude = this->magnitude();
    return Vector(x / magnitude, y / magnitude);
  }

  void set_magnitude(double magnitude);

  friend std::ostream &operator<<(std::ostream &os, const Vector &m);
};

//============== Operators =============//
inline Vector operator+(const Vector &left, const Vector &right) {
  return Vector(left.x + right.x, left.y + right.y);
}

inline Vector operator-(const Vector &left, const Vector &right) {
  return Vector(left.x - right.x, left.y - right.y);
}

inline Vector operator*(const Vector &left, double constant) {
  return Vector(left.x * constant, left.y * constant);
}

inline Vector operator*(double constant, const Vector &right) {
  return Vector(right.x * constant, right.y * constant);
}

inline Vector operator/(const Vector &left, double constant) {
  return Vector(left.x / constant, left.y / constant);
}

inline Vector operator-(const Vector &vector) {
  return Vector(-vector.x, -vector.y);
}

#endif
