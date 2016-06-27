#ifndef _AMNESIA_ENTITY_HEADER_
#define _AMNESIA_ENTITY_HEADER_

#include <memory>
#include <vector>
#include <map>

class Component;

class Entity {

public:

    Entity();
    Entity(std::vector<Vector> vertices);
    ~Entity() = default;

    template <typename T>
    void add_component(std::shared_ptr<T> component);

    template <typename T>
    void remove_component();

    template <typename T>
    void remove_components();

    template <typename T>
    bool has_component();

    // Operators
    friend std::ostream &operator<<(std::ostream &os, const Entity &m);

private:

    std::vector<std::shared_ptr<Component>> components;
    std::map<std::string, int> type_count;

};

#include "component.h"
#include "entity.tpp"

#endif