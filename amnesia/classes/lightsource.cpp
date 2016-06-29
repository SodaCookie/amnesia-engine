#include "../primitive/segment.h"
#include "entity.h"
#include "lightsource.h"
#include <utility>
#include <algorithm>
#include <limits>

LightSource::LightSource() : Component() {
}

LightSource::LightSource(Vector position, double radius, double strength) :
    Component(), position(position), radius(radius), strength(strength) {
}

void LightSource::move(Vector new_position) {
    position = new_position;
}

std::vector<Polygon> LightSource::process(
        std::vector<Polygon> polygons, Polygon view) {
    std::vector<Segment> segments = std::vector<Segment>();
    std::vector<Vector> points = std::vector<Vector>();

    // Add current points and segments
    for (auto polygon : polygons) {
        for (auto point : polygon.get_vertices()) {
            points.push_back(point);
        }
        for (auto segment : polygon.get_sides()) {
            segments.push_back(segment);
        }
    }

    // Create rays to test
    Vector rel_position = position + owner->transform;
    std::vector<Segment> rays = std::vector<Segment>();
    for (auto point : points) {
        Vector direction = point - rel_position;
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
    for (auto ray : rays) {
        std::pair<bool, Vector> closest_intersection (false, Vector());
        double closest_magnitude = std::numeric_limits<double>::max();
        for (auto segment : segments) {
            std::pair<bool, Vector> intersect = segment.intersect_ray(ray);
            if (intersect.first) {
                Vector distance = intersect.second - rel_position;
                if (!closest_intersection.first or
                        distance.magnitude() <= closest_magnitude){
                    closest_intersection = std::make_pair(true, distance);
                    closest_magnitude = distance.magnitude();
                }
            }
        }
        if (closest_intersection.first) {
            intersections.push_back(closest_intersection.second);
        }
    }

    // Sort intersects by angle
    std::sort(intersections.begin(), intersections.end(),
        [] (const Vector &i, const Vector &j) -> bool {
            return i.angle(Vector::right) < j.angle(Vector::right);
        });

    // Calculate light blocks
    std::vector<Polygon> blocks = std::vector<Polygon>();
    for (unsigned int i = 0; i < intersections.size(); i++) {
        std::vector<Vector> triangle_points = std::vector<Vector>();
        triangle_points.push_back(rel_position);
        triangle_points.push_back(intersections[i] + rel_position);
        triangle_points.push_back(
            intersections[(i+1) % intersections.size()] + rel_position);
        blocks.push_back(Polygon(triangle_points));
    }

    return blocks;
}