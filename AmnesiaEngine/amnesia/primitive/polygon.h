#ifndef _AMNESIA_POLYGON_HEADER_
#define _AMNESIA_POLYGON_HEADER_

#include "rect.h"
#include "segment.h"
#include "vector.h"
#include <ostream>
#include <utility>
#include <vector>

class Polygon {

public:
  Rect bounding_rect;

  Polygon();
  Polygon(std::vector<Vector> vertices);

  template <typename... Ts> Polygon(Ts... points) {
    vertices = std::vector<Vector>({points...});
    double min_x = std::numeric_limits<double>::max();
    double min_y = std::numeric_limits<double>::max();
    double max_x = std::numeric_limits<double>::min();
    double max_y = std::numeric_limits<double>::min();

    // Add current points and segments
    for (unsigned int i = 0, j = 1; i < vertices.size(); i++, j++) {
      auto first = vertices[i];
      auto second = vertices[j % vertices.size()];
      // Maintain calculate bounds
      min_x = std::min(min_x, first.x);
      max_x = std::max(max_x, first.x);
      min_y = std::min(min_y, first.y);
      max_y = std::max(max_y, first.y);
      sides.push_back(Segment(first, second - first));
    }

    bounding_rect = Rect(min_x, min_y, max_x - min_x, max_y - min_y);
  }

  ~Polygon() = default;

  std::vector<Vector> get_vertices() const;

  std::vector<Segment> get_sides() const;

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
