#ifndef _AMNESIA_ENGINE_HEADER_
#define _AMNESIA_ENGINE_HEADER_

#include <string>
#include <vector>
#include <map>
#include <memory>
#include "window.h"
#include "time.h"
#include "input.h"
#include "message.h"
#include "../classes/entity.h"

class System;

class GameEngine : public std::enable_shared_from_this<GameEngine> {

public:

    GameEngine();

    void add_system(std::shared_ptr<System> system);

    void add_entity(std::shared_ptr<Entity> e);

    std::shared_ptr<Entity> find(std::string name);

    void message(std::string system, std::shared_ptr<IMessage> message);

    void run();

    void quit();

    WindowSystem Window;
    InputSystem Input;
    TimeSystem Time;
    std::map<std::string, std::shared_ptr<Entity>> Entities;

private:

    std::map<std::string, std::shared_ptr<System>> systems;
    bool running;

};

#endif
