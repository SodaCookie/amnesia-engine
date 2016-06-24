#ifndef _AMNESIA_VECTOR_HEADER_
#define _AMNESIA_VECTOR_HEADER_

#include <ostream>

class Vector {

public:

    double x, y;
    const static Vector up;
    const static Vector down;
    const static Vector right;
    const static Vector left;

    Vector();
    Vector(double x, double y);
    ~Vector() = default;

    double magnitude();

    double angle(const Vector &reference);

    void set_magitude(double magnitude);

    double dot(const Vector &other);

    Vector rotate(double angle);

    bool parallel(const Vector &other);

    Vector normalized();

    // Operators
    friend Vector operator+(const Vector &left, const Vector &right);
    friend Vector operator-(const Vector &left, const Vector &right);
    friend Vector operator*(const Vector &left, const Vector &right);
    friend Vector operator/(const Vector &left, const Vector &right);
    friend std::ostream &operator<<(std::ostream &os, const Vector &m);
    friend Vector operator-(const Vector &vector);
};

#endif