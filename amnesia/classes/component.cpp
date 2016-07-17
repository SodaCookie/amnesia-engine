#include "component.h"

Component::Component() {}

void Component::set_owner(std::shared_ptr<Entity> entity) { owner = entity; }

void Component::init() {}

//============== Operators =============//

std::ostream &operator<<(std::ostream &os, const Component &m) {
  return os << std::string(typeid(m).name());
}
