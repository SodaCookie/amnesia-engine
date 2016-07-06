#ifndef _AMNESIA_SYSTEM_HEADER_
#define _AMNESIA_SYSTEM_HEADER_

#include <string>
#include <vector>
#include <memory>
#include "message.h"
#include "../classes/entity.h"

class GameEngine;

class System {

public:

    friend class Engine;

    System(std::string name);

    virtual void init() = 0;

    virtual void update() = 0;

    virtual void quit() = 0;

    void add_message(std::shared_ptr<IMessage> message);

protected:

    std::shared_ptr<GameEngine> Engine;
    std::vector<std::shared_ptr<IMessage>> messages;
    std::string name;

    std::vector<std::shared_ptr<IMessage>> flush_messages();

};

#endif