#ifndef _AMNESIA_ENTITY_HEADER_
#define _AMNESIA_ENTITY_HEADER_

#include "../primitive/vector.h"
#include <map>
#include <memory>
#include <string>
#include <typeinfo>
#include <vector>

class Component;
class Script;

class Entity : public std::enable_shared_from_this<Entity> {

public:
  bool destroy;
  std::string name;
  Vector transform;

  Entity(std::string name);
  Entity(std::string name, Vector transform);
  ~Entity() = default;

  template <typename T, typename... Args>
  std::shared_ptr<T> add_component(Args... args);

  template <typename T> void remove_component();

  template <typename T> void remove_components();

  template <typename T> int has_component();

  template <typename T> std::shared_ptr<T> get_component();

  template <typename T> std::vector<std::shared_ptr<T>> get_components();

  // Operators
  friend std::ostream &operator<<(std::ostream &os, const Entity &m);

private:
  std::map<std::string, std::vector<std::shared_ptr<Component>>> components;

  std::shared_ptr<Component>
  _add_component(std::shared_ptr<Component> component);
};

template <typename T> void Entity::remove_component() {
  std::string component_type = typeid(T).name();
  components[component_type].pop_back();
  if (components.count(component_type) == 0) {
    components.erase(component_type);
  }
}

template <typename T, typename... Args>
std::shared_ptr<T> Entity::add_component(Args... args) {
  std::shared_ptr<T> component = std::make_shared<T>(args...);
  std::string component_type = typeid(*component).name();
  if (components.count(component_type) == 0) {
    components[component_type] = std::vector<std::shared_ptr<Component>>();
  }
  components[component_type].push_back(component);
  return std::static_pointer_cast<T>(_add_component(component));
}

template <typename T> void Entity::remove_components() {
  components.erase(typeid(T).name());
}

template <typename T> int Entity::has_component() {
  return components.count(typeid(T).name());
}

template <typename T> std::shared_ptr<T> Entity::get_component() {
  return components[typeid(T).name()][0];
}

template <typename T> std::vector<std::shared_ptr<T>> Entity::get_components() {
  return components[typeid(T).name()];
}

#endif
