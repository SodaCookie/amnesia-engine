#ifndef _AMNESIA_RENDERER_HEADER_
#define _AMNESIA_RENDERER_HEADER_

#include "component.h"

class Renderer : public Component, public std::enable_shared_from_this<Script> {

public:
  void init() override;
  virtual void render() = 0;
};

#endif
