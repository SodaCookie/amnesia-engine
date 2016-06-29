#include <cmath>
#include "vector.h"

Vector::Vector() : x(0.0), y(0.0) {
}

Vector::Vector(double x, double y) : x(x), y(y) {
}

//============== Static Members =============//
const Vector Vector::up = Vector(0, 1);
const Vector Vector::down = Vector(0, 1);
const Vector Vector::right = Vector(0, 1);
const Vector Vector::left = Vector(0, 1);

//============== Utility =============//
double Vector::magnitude() const {
    return std::sqrt(x * x + y * y);
}

double Vector::angle(const Vector &reference) const {
    return std::atan2(y, x) - std::atan2(reference.y, reference.x);
}

void Vector::set_magitude(double magnitude) {
    double old_magnitude = this->magnitude();
    double ratio = magnitude / old_magnitude;
    x *= ratio;
    y *= ratio;
}

double Vector::dot(const Vector &other) const {
    return x * other.x + y * other.y;
}

Vector Vector::rotate(double angle) const {
    double new_x = cos(angle) * x - sin(angle) * y;
    double new_y = sin(angle) * x + cos(angle) * y;
    return Vector(new_x, new_y);
}

bool Vector::parallel(const Vector &other) const {
    double epsilon = 0.00001;
    double angle = this->angle(other);

    if (abs(angle) < epsilon || abs(3.14159265358 - angle) < epsilon) {
        return true;
    }
    return false;
}

Vector Vector::normalized() const {
    double magnitude = this->magnitude();
    return Vector(x / magnitude, y / magnitude);
}

//============== Operators =============//
Vector operator+(const Vector &left, const Vector &right) {
    return Vector(left.x + right.x, left.y + right.y);
}

Vector operator-(const Vector &left, const Vector &right) {
    return Vector(left.x - right.x, left.y - right.y);
}

Vector operator*(const Vector &left, double &constant) {
    return Vector(left.x * constant, left.y * constant);
}

Vector operator/(const Vector &left, double &constant) {
    return Vector(left.x / constant, left.y / constant);
}

std::ostream &operator<<(std::ostream &os, const Vector &vector) {
    return os << "Vector(" << vector.x << ", " << vector.y << ")";
}

Vector operator-(const Vector &vector) {
    return Vector(-vector.x, -vector.y);
}