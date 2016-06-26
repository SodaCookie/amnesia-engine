#include "polygon.h"

Polygon::Polygon() {
}

Polygon::Polygon(std::vector<Vector> vertices) : vertices(vertices){
    for (unsigned int i = 0, j = 1; i < vertices.size(); i++, j++) {
        auto first = vertices[i];
        auto second = vertices[j % vertices.size()];

        sides.push_back(Segment(first, second - first));
    }
}

std::vector<Vector> Polygon::get_vertices() {
    return vertices;
}

std::vector<Segment> Polygon::get_sides() {
    return sides;
}

void Polygon::move(Vector point) {

}

bool Polygon::collidepoint(Vector point) {
    return true;
}

bool Polygon::colliderangex(double y) {
    return true;
}

//============== Operators =============//

// Polygon operator+(const Polygon &left, const Vector &right) {

// }

std::ostream &operator<<(std::ostream &os, const Polygon &m) {
    os << "Polygon(\n";
    for (auto vertex : m.vertices) {
        os << "\t" << vertex << "/n";
    }
    os << ")";
    return os;
}