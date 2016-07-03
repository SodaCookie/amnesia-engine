#ifndef _AMNESIA_SYSTEM_HEADER_
#define _AMNESIA_SYSTEM_HEADER_

#include <string>
#include <vector>
#include <memory>
#include "message.h"
#include "../classes/entity.h"

class Engine;

class System {

public:

    System(std::string name, std::shared_ptr<Engine> engine);

    virtual void init(std::vector<std::shared_ptr<Entity>> entities) = 0;

    virtual void update(double delta,
        std::vector<std::shared_ptr<Entity>> entities) = 0;

    virtual void quit(std::vector<std::shared_ptr<Entity>> entities) = 0;

    void add_message(std::unique_ptr<IMessage> message);

protected:

    std::shared_ptr<Engine> engine;
    std::vector<std::unique_ptr<IMessage>> messages;
    std::string name;

    std::vector<std::unique_ptr<IMessage>> flush_messages();

};

#endif