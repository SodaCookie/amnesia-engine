#include "../primitive/segment.h"
#include "entity.h"
#include "lightsource.h"
#include <utility>
#include <algorithm>
#include <limits>
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

int LightSource::Precision = 360;

LightSource::LightSource() : Component() {
}

LightSource::LightSource(Vector position, double radius, double strength) :
        Component(), position(position), radius(radius), strength(strength) {
    // Generate rays (360 is the number of rays to test)
    radial_vectors.reserve(LightSource::Precision);
    for (double i = 0; i < LightSource::Precision; i++){
        radial_vectors.push_back(Segment(Vector(0, 0),
            Vector(
                radius * cos(i / LightSource::Precision * 360 * M_PI / 180),
                radius * sin(i / LightSource::Precision * 360 * M_PI / 180)
            )));
    }
}

void LightSource::move(Vector new_position) {
    position = new_position;
}

std::vector<Polygon> LightSource::process(
        std::vector<Polygon> polygons, Polygon view) {
    // Gather all polygons
    std::vector<Segment> segments = std::vector<Segment>();

    // Add current points and segments
    for (auto polygon : polygons) {
        for (auto segment : polygon.get_sides()) {
            segments.push_back(segment);
        }
    }

    // add view to model
    for (auto segment : view.get_sides()) {
        segments.push_back(segment);
    }

    // Create rays to test
    Vector rel_position = position;// + owner->transform;

    // Returned list of blocks
    std::vector<Polygon> blocks = std::vector<Polygon>();

    // For block building
    bool seen_previous;
    Vector previous_intersection;
    Vector first_intersection;

    // For intersect detection
    Segment current_ray; // Per ray the current closest

    for (auto current_ray : radial_vectors) {
        current_ray.anchor = rel_position;
        for (auto segment : segments) {
            std::pair<bool, Vector> intersect =
                current_ray.intersect_segment(segment);
            if (intersect.first) {
                current_ray.direction = intersect.second - current_ray.anchor;
            }
        }

        // Build the next block
        if (seen_previous) {
            blocks.push_back(Polygon(
                std::vector<Vector>({
                    rel_position,
                    previous_intersection,
                    current_ray.direction + current_ray.anchor
                })
            ));
            previous_intersection = current_ray.direction + current_ray.anchor;
        }
        else {
            first_intersection = current_ray.direction + current_ray.anchor;
            previous_intersection = current_ray.direction + current_ray.anchor;
            seen_previous = true;
        }
    }
    blocks.push_back(Polygon(
        std::vector<Vector>({
            rel_position,
            previous_intersection,
            first_intersection
        })
    ));
    return blocks;
}
