#ifndef _AMNESIA_POLYGON_HEADER_
#define _AMNESIA_POLYGON_HEADER_

#include <ostream>
#include <vector>
#include <utility>
#include <algorithm>
#include "vector.h"
#include "segment.h"

class Polygon {

public:

    Polygon();
    Polygon(std::vector<Vector> vertices);
    ~Polygon() = default;

    std::vector<Vector> get_vertices();

    std::vector<Segment> get_sides();

    void move(const Vector &point);

    int collidepoint(Vector point);

    std::vector<std::pair<int, int>> colliderangex(double y);

    // Operators
    friend Polygon operator+(const Polygon &left, const Vector &right);
    friend std::ostream &operator<<(std::ostream &os, const Polygon &m);

private:

    std::vector<Vector> vertices;
    std::vector<Segment> sides;

};

#endif