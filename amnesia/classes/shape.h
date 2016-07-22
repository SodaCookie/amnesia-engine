#ifndef _AMNESIA_SHAPE_HEADER_
#define _AMNESIA_SHAPE_HEADER_

#include "../primitive/polygon.h"
#include "component.h"
#include <memory>

class Shape : public Component {
public:
  bool light_active;
  std::shared_ptr<Polygon> polygon;

  Shape();
  Shape(std::shared_ptr<Polygon> polygon);
};

#endif
