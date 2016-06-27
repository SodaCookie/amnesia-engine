#ifndef _AMNESIA_COMPONENT_HEADER_
#define _AMNESIA_COMPONENT_HEADER_

#include <memory>

class Entity;

class Component {

public:

    Component();
    ~Component() = default;

    void set_owner(std::shared_ptr<Entity> entity);

    // Operators
    friend std::ostream &operator<<(std::ostream &os, const Component &m);

protected:

    std::shared_ptr<Entity> entity;

};

#include "entity.h"

#endif