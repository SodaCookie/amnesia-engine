#ifndef _AMNESIA_SEGMENT_HEADER_
#define _AMNESIA_SEGMENT_HEADER_

#include "vector.h"
#include <ostream>
#include <utility>

class Segment {

public:
  Vector anchor;
  Vector direction;

  Segment();
  Segment(Vector anchor, Vector direction);
  ~Segment() = default;

  std::pair<bool, Vector> intersect_segment(const Segment &other) const;

  bool intersect_segment(const Segment &other, Vector &out) const;

  std::pair<bool, Vector> intersect_ray(const Segment &other) const;

  bool intersect_ray(const Segment &other, Vector &out) const;

  std::pair<bool, Vector> intersect_line(const Segment &other) const;

  // Operators
  friend std::ostream &operator<<(std::ostream &os, const Segment &m);
};

#endif
