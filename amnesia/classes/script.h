#ifndef _AMNESIA_SCRIPT_HEADER_
#define _AMNESIA_SCRIPT_HEADER_

#include "component.h"

class Script : public Component, public std::enable_shared_from_this<Script> {

public:
  void init() override;
  virtual void update() = 0;
};

#endif
