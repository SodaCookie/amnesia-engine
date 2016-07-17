#include "lightsource.h"
#include "../primitive/rect.h"
#include "../primitive/segment.h"
#include "entity.h"
#include <algorithm>
#include <limits>
#include <utility>
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

int LightSource::Precision = 360;

LightSource::LightSource() : Component() {}

LightSource::LightSource(Vector position, double radius, double strength)
    : Component(), position(position), radius(radius), strength(strength) {}

void LightSource::move(Vector new_position) { position = new_position; }

std::vector<Polygon> LightSource::process(std::vector<Polygon> &polygons) {
  std::vector<Segment> segments = std::vector<Segment>();
  std::vector<Vector> points = std::vector<Vector>();
  Vector rel_position = position; // + owner->transform;
  double min_x = rel_position.x - radius;
  double min_y = rel_position.y - radius;
  double max_x = rel_position.x + radius;
  double max_y = rel_position.y + radius;

  // Rect
  Rect camera_bound = Rect(rel_position.x - radius, rel_position.y - radius,
                           radius * 2, radius * 2);
  // Add current points and segments

  for (auto &polygon : polygons) {
    // if (camera_bound.intersect_rect(polygon.bounding_rect)) {
    if (true) {
      for (const auto &point : polygon.get_vertices()) {
        min_x = std::min(min_x, point.x);
        max_x = std::max(max_x, point.x);
        min_y = std::min(min_y, point.y);
        max_y = std::max(max_y, point.y);
        points.push_back(point);
      }
      for (auto &segment : polygon.get_sides()) {
        segments.push_back(segment);
      }
    }
  }

  // Construct view
  Polygon view = Polygon(Vector(min_x, min_y), Vector(max_x, min_y),
                         Vector(max_x, max_y), Vector(min_x, max_y));

  // add view to model
  for (const auto &point : view.get_vertices()) {
    points.push_back(point);
  }
  for (auto &segment : view.get_sides()) {
    segments.push_back(segment);
  }

  // Create rays to test
  double max_length = std::max(max_x - min_x, max_y - min_y) * 2;
  std::vector<Segment> rays = std::vector<Segment>();
  for (const auto &point : points) {
    Vector direction = point - rel_position;
    direction.set_magnitude(max_length);
    Segment ray_left = Segment(rel_position, direction.rotate(-0.00001));
    Segment ray = Segment(rel_position, direction);
    Segment ray_right = Segment(rel_position, direction.rotate(0.00001));
    if (ray.direction.magnitude() == 0) {
      continue;
    }
    rays.push_back(ray_left);
    rays.push_back(ray);
    rays.push_back(ray_right);
  }

  // Test all intersections
  std::vector<Vector> intersections = std::vector<Vector>();
  Vector intersect;

  for (auto &ray : rays) {
    for (const auto &segment : segments) {
      if (ray.intersect_segment(segment, intersect)) {
        ray.direction = intersect - ray.anchor;
      }
    }
    intersections.push_back(Vector(ray.direction));
  }

  // Sort intersects by angle
  std::sort(
      intersections.begin(), intersections.end(),
      [](const Vector &i, const Vector &j) -> bool { return i.cross(j) > 0; });

  // Calculate light blocks
  std::vector<Polygon> blocks = std::vector<Polygon>();
  for (unsigned int i = 0; i < intersections.size(); i++) {
    std::vector<Vector> triangle_points = std::vector<Vector>();
    triangle_points.push_back(rel_position);
    triangle_points.push_back(intersections[i] + rel_position);
    triangle_points.push_back(intersections[(i + 1) % intersections.size()] +
                              rel_position);
    blocks.push_back(Polygon(triangle_points));
  }

  return blocks;
}
