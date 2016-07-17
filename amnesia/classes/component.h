#ifndef _AMNESIA_COMPONENT_HEADER_
#define _AMNESIA_COMPONENT_HEADER_

#include <memory>
#include <ostream>
#include <string>
#include <typeinfo>

class Entity;

class Component {

public:
  Component();
  ~Component() = default;

  void set_owner(std::shared_ptr<Entity> entity);

  virtual void init();

  // Operators
  friend std::ostream &operator<<(std::ostream &os, const Component &m);

protected:
  std::shared_ptr<Entity> owner;
};

#endif
