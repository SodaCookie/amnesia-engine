#ifndef _AMNESIA_SCRIPT_HEADER_
#define _AMNESIA_SCRIPT_HEADER_

#include "component.h"

class Script : public Component {

public:
  bool destroy = false;
  virtual void update() = 0;
};

#endif
