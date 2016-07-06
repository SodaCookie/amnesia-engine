#include "engine.h"

Engine::Engine() {
    Window = WindowSystem(640, 480);
    Input = InputSystem();
    Time = TimeSystem();
}

void Engine::add_system(std::shared_ptr<System> system) {
    system->engine = shared_from_this();
    systems[system->name] = system;
}

void Engine::add_entity(Entity e) {
    Entities[e.name] = e;
}

Entity& Engine::find(std::string name) {
    return Entities[name];
}

void Engine::message(std::string system, std::shared_ptr<IMessage> message) {
    systems[system]->add_message(message);
}

void Engine::run() {
    running = true;

    // Initiate
    Window.init();
    Input.init();
    Time.init();

    for (auto system : systems) {
        system->init();
    }

    // Main Game Loop

    while (running) {
        Window.update();
        Input.update();
        Time.update();
        for (auto system : systems) {
            system->update();
        }
        Window.flip();
    }

    // Quit
    for (auto system : systems) {
        system->quit();
    }

    Window.quit();
    Input.quit();
    Time.quit();
}

void Engine::quit() {
    running = false;
}