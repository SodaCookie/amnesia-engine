#include "polygon.h"
#include <algorithm>
#include <limits>

Polygon::Polygon() {}

Polygon::Polygon(std::vector<Vector> vertices) : vertices(vertices) {
  double min_x = std::numeric_limits<double>::max();
  double min_y = std::numeric_limits<double>::max();
  double max_x = std::numeric_limits<double>::min();
  double max_y = std::numeric_limits<double>::min();
  // Add current points and segments
  for (Vector &point : vertices) {
    // Maintain calculate bounds
    min_x = std::min(min_x, point.x);
    max_x = std::max(max_x, point.x);
    min_y = std::min(min_y, point.y);
    max_y = std::max(max_y, point.y);
  }
  bounding_rect = Rect(min_x, min_y, max_x - min_x, max_y - min_y);
}

std::vector<Vector> Polygon::get_vertices() const { return vertices; }

std::vector<Segment> Polygon::get_sides() {
  if (sides.empty()) {
    for (unsigned int i = 0, j = 1; i < vertices.size(); i++, j++) {
      auto first = vertices[i];
      auto second = vertices[j % vertices.size()];
      sides.push_back(Segment(first, second - first));
    }
  }
  return sides;
}

void Polygon::move(const Vector &point) {
  // Move vertices
  for (auto vertex : vertices) {
    vertex.x += point.x;
    vertex.y += point.y;
  }

  // Move edges
  for (auto edge : sides) {
    edge.anchor.x += point.x;
    edge.anchor.y += point.y;
  }

  // Move bounding box
  bounding_rect.x += point.x;
  bounding_rect.y += point.y;
}

int Polygon::collidepoint(Vector point) {
  Segment horizontal_line = Segment(Vector(0, point.y), Vector::right);
  std::pair<bool, Vector> intersect;
  int left = 0;
  for (const auto &edge : sides) {
    intersect = edge.intersect_line(horizontal_line);
    if (intersect.first and intersect.second.x < point.x) {
      left++;
    }
  }
  return left % 2;
}

std::vector<std::pair<int, int>> Polygon::colliderangex(double y) {
  Segment horizontal_line = Segment(Vector(0, y), Vector::right);
  std::vector<int> points;
  std::vector<std::pair<int, int>> intersects;
  std::pair<bool, Vector> intersect;

  for (const auto &edge : sides) {
    intersect = edge.intersect_line(horizontal_line);
    if (intersect.first) {
      points.push_back(intersect.second.x);
    }
  }
  std::sort(points.begin(), points.end());
  for (unsigned int i = 0; i < points.size() / 2; i++) {
    intersects.push_back(std::make_pair(points[i], points[i + 1]));
  }
  return intersects;
}

//============== Operators =============//

Polygon operator+(const Polygon &left, const Vector &right) {
  std::vector<Vector> new_points;
  // Move vertices
  for (auto vertex : left.vertices) {
    vertex.x += right.x;
    vertex.y += right.y;
  }

  return Polygon(new_points);
}

std::ostream &operator<<(std::ostream &os, const Polygon &m) {
  os << "Polygon(\n";
  for (auto vertex : m.vertices) {
    os << "\t" << vertex << "/n";
  }
  os << ")";
  return os;
}
