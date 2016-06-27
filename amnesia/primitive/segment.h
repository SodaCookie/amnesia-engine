#ifndef _AMNESIA_SEGMENT_HEADER_
#define _AMNESIA_SEGMENT_HEADER_

#include <ostream>
#include <utility>
#include "vector.h"

class Segment {

public:

    Vector anchor;
    Vector direction;

    Segment();
    Segment(Vector anchor, Vector direction);
    ~Segment() = default;

    std::pair<bool, Vector> intersect_segment(const Segment &other);

    std::pair<bool, Vector> intersect_ray(const Segment &other);

    std::pair<bool, Vector> intersect_line(const Segment &other);

    // Operators
    friend std::ostream &operator<<(std::ostream &os, const Segment &m);
};

#endif