#ifndef _AMNESIA_LIGHTSOURCE_HEADER_
#define _AMNESIA_LIGHTSOURCE_HEADER_

#include "../primitive/vector.h"
#include "../primitive/polygon.h"
#include "component.h"
#include <vector>

class LightSource : public Component {

public:

    static int Precision;

    LightSource();
    LightSource(Vector position, double radius, double strength = 1.0);
    ~LightSource() = default;

    void move(Vector new_position);

    std::vector<Polygon> process(std::vector<Polygon> polygons, Polygon view);

private:

    Vector position;
    double radius;
    double strength;
    std::vector<Segment> radial_vectors;

};

#endif
