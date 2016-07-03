#include <iostream>
#include "amnesia/primitive/vector.h"
#include "amnesia/primitive/segment.h"
#include "amnesia/classes/component.h"
#include "amnesia/core/message.h"

#include <tuple>

int main(int argc, char *argv[]) {
    Vector v1(1, 1);
    Vector v2(1.0, -2.0);
    Component c = Component();
    Message<int, int> m = Message<int, int>("hello", 1, 1);
    std::cout << std::get<0>(m.data) << ", " << std::get<1>(m.data) << std::endl;

    std::cout << (v1 + v2) << std::endl;
    std::cout << v2.normalized().magnitude() << std::endl;
    std::cout << Vector::up << std::endl;

    std::cout << Segment(v1, v2);
}