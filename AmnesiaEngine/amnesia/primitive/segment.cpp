#include "segment.h"
#include <cmath>

Segment::Segment() {}

Segment::Segment(Vector anchor, Vector direction) : anchor(anchor), direction(direction) {}

std::pair<bool, Vector> Segment::intersect_segment(const Segment &other) const {
  double rs = direction.cross(other.direction);

  if (std::abs(rs) > 0.000001) {
    double t = (other.anchor - anchor).cross(other.direction) / rs;
    double u = (other.anchor - anchor).cross(direction) / rs;
    return std::pair<bool, Vector>((t >= 0 && t <= 1) && (u >= 0 && u <= 1),
                                   Vector(anchor + (t * direction)));
  } else {
    return std::pair<bool, Vector>(false, Vector());
  }
}

bool Segment::intersect_segment(const Segment &other, Vector &out) const {
  double rs = direction.cross(other.direction);

  if (std::abs(rs) > 0.000001) {
    double t = (other.anchor - anchor).cross(other.direction) / rs;
    double u = (other.anchor - anchor).cross(direction) / rs;
    bool ret = (t >= 0 && t <= 1) && (u >= 0 && u <= 1);
    if (!ret) {
      return false;
    }
    out.x = anchor.x + t * direction.x;
    out.y = anchor.y + t * direction.y;
    return true;
  } else {
    return false;
  }
}

std::pair<bool, Vector> Segment::intersect_ray(const Segment &other) const {
  double rs = direction.cross(other.direction);

  if (std::abs(rs) > 0.000001) {
    double t = (other.anchor - anchor).cross(other.direction) / rs;
    double u = (other.anchor - anchor).cross(direction) / rs;
    return std::pair<bool, Vector>((t >= 0 && t <= 1) && (u >= 0),
                                   Vector(anchor + (t * direction)));
  } else {
    return std::pair<bool, Vector>(false, Vector());
  }
}

bool Segment::intersect_ray(const Segment &other, Vector &out) const {
  double rs = direction.cross(other.direction);

  if (std::abs(rs) > 0.000001) {
    double t = (other.anchor - anchor).cross(other.direction) / rs;
    double u = (other.anchor - anchor).cross(direction) / rs;
    bool ret = (t >= 0 && t <= 1) && (u >= 0);
    if (!ret) {
      return false;
    }
    out.x = anchor.x + t * direction.x;
    out.y = anchor.y + t * direction.y;
    return true;
  } else {
    return false;
  }
}

std::pair<bool, Vector> Segment::intersect_line(const Segment &other) const {
  double rs = direction.cross(other.direction);

  if (std::abs(rs) > 0.000001) {
    double t = (other.anchor - anchor).cross(other.direction) / rs;
    return std::pair<bool, Vector>((t >= 0 && t <= 1), Vector(anchor + (t * direction)));
  } else {
    return std::pair<bool, Vector>(false, Vector());
  }
}

bool Segment::intersect_line(const Segment &other, Vector &out) const {
  double rs = direction.cross(other.direction);

  if (std::abs(rs) > 0.000001) {
    double t = (other.anchor - anchor).cross(other.direction) / rs;
    bool ret = (t >= 0 && t <= 1);
    if (!ret) {
      return false;
    }
    out.x = anchor.x + t * direction.x;
    out.y = anchor.y + t * direction.y;
    return true;
  } else {
    return false;
  }
}

//================ Operators ================//

std::ostream &operator<<(std::ostream &os, const Segment &m) {
  return os << "Segment(" << m.anchor << ", " << m.direction << ")";
}
