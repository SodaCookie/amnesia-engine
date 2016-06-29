#include "segment.h"
#include <cmath>

Segment::Segment() {
}

Segment::Segment(Vector anchor, Vector direction) :
        anchor(anchor), direction(direction){
}

std::pair<bool, Vector> Segment::intersect_segment(const Segment &other) {
    if (direction.parallel(other.direction)){
        return std::make_pair(false, Vector());
    }

    // Test intersection
    double px1 = anchor.x, dx1 = direction.x;
    double px2 = other.anchor.x, dx2 = other.direction.x;
    double py1 = anchor.y, dy1 = direction.y;
    double py2 = other.anchor.y, dy2 = other.direction.y;
    double t1, t2;

    if (std::abs(dx2*dy1 - dy2*dx1) > 0.000001) {
        t2 = (dx1*(py2-py1) + dy1*(px1-px2)) / (dx2*dy1 - dy2*dx1);
    }
    else {
        t2 = (dx1*(py2-py1) + dy1*(px1-px2)) / 0.000001;
    }

    if (std::abs(dx1) > 0.000001) {
        t1 = (px2+dx2*t2-px1) / dx1;
    }
    else {
        t1 = (py2+dy2*t2-py1) / dy1;
    }

    if ((0.0 <= t1 and t1 <= 1.0) and (0.0 <= t2 and t2 <= 1.0)) {
        return std::make_pair(true, Vector(px1 + dx1 * t1, py1 + dy1 * t1));
    }
    return std::make_pair(false, Vector());
}

std::pair<bool, Vector> Segment::intersect_ray(const Segment &other) {
    if (direction.parallel(other.direction)){
        return std::make_pair(false, Vector());
    }

    // Test intersection
    double px1 = anchor.x, dx1 = direction.x;
    double px2 = other.anchor.x, dx2 = other.direction.x;
    double py1 = anchor.y, dy1 = direction.y;
    double py2 = other.anchor.y, dy2 = other.direction.y;
    double t1, t2;

    if (std::abs(dx2*dy1 - dy2*dx1) > 0.000001) {
        t2 = (dx1*(py2-py1) + dy1*(px1-px2)) / (dx2*dy1 - dy2*dx1);
    }
    else {
        t2 = (dx1*(py2-py1) + dy1*(px1-px2)) / 0.000001;
    }

    if (std::abs(dx1) > 0.000001) {
        t1 = (px2+dx2*t2-px1) / dx1;
    }
    else {
        t1 = (py2+dy2*t2-py1) / dy1;
    }

    if ((0.0 <= t1 and t1 <= 1.0) and 0.0 <= t2) {
        return std::make_pair(true, Vector(px1 + dx1 * t1, py1 + dy1 * t1));
    }
    return std::make_pair(false, Vector());
}

std::pair<bool, Vector> Segment::intersect_line(const Segment &other) {
    if (direction.parallel(other.direction)){
        return std::make_pair(false, Vector());
    }

    // Test intersection
    double px1 = anchor.x, dx1 = direction.x;
    double px2 = other.anchor.x, dx2 = other.direction.x;
    double py1 = anchor.y, dy1 = direction.y;
    double py2 = other.anchor.y, dy2 = other.direction.y;
    double t1, t2;

    if (std::abs(dx2*dy1 - dy2*dx1) > 0.000001) {
        t2 = (dx1*(py2-py1) + dy1*(px1-px2)) / (dx2*dy1 - dy2*dx1);
    }
    else {
        t2 = (dx1*(py2-py1) + dy1*(px1-px2)) / 0.000001;
    }

    if (std::abs(dx1) > 0.000001) {
        t1 = (px2+dx2*t2-px1) / dx1;
    }
    else {
        t1 = (py2+dy2*t2-py1) / dy1;
    }

    if (0.0 <= t1 and t1 <= 1.0) {
        return std::make_pair(true, Vector(px1 + dx1 * t1, py1 + dy1 * t1));
    }
    return std::make_pair(false, Vector());
}

//================ Operators ================//

std::ostream &operator<<(std::ostream &os, const Segment &m){
    return os << "Segment(" << m.anchor << ", " << m.direction << ")";
}