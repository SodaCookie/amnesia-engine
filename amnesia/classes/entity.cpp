#include "entity.h"
#include "component.h"

Entity::Entity(std::string name) : name(name) {
}

std::string Entity::get_name() {
    return name;
}

std::shared_ptr<Component> Entity::_add_component(
        std::shared_ptr<Component> component) {
    std::string component_type = typeid(*component).name();
    if (components.count(component_type) == 0) {
        components[component_type] = std::vector<std::shared_ptr<Component>>();
    }
    components[component_type].push_back(component);
    component->set_owner(shared_from_this());
    return component;
}

//============== Operators =============//

std::ostream &operator<<(std::ostream &os, const Entity &m) {
    return os << "Entity(" + m.name + ")";
}