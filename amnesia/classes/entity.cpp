#include "entity.h"
#include "../core/engine.h"
#include "component.h"
#include "script.h"

Entity::Entity(std::string name) : destroy(false), name(name) {}

Entity::Entity(std::string name, Vector transform)
    : destroy(false), name(name), transform(transform) {}

std::shared_ptr<Component>
Entity::_add_component(std::shared_ptr<Component> component) {
  component->set_owner(shared_from_this());
  component->init();
}

//============== Operators =============//

std::ostream &operator<<(std::ostream &os, const Entity &m) {
  return os << "Entity(" + m.name + ")";
}
