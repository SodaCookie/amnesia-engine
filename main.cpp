#include <iostream>
#include "amnesia/classes/vector.h"
#include "amnesia/classes/segment.h"

int main(int argc, char *argv[]) {
    Vector v1(1, 1);
    Vector v2(1.0, -2.0);

    std::cout << (v1 + v2) << std::endl;
    std::cout << v2.normalized().magnitude() << std::endl;
    std::cout << Vector::up << std::endl;

    std::cout << Segment(v1, v2);
}