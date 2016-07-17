#include "engine.h"

std::shared_ptr<GameEngine> Engine = std::make_shared<GameEngine>();

GameEngine::GameEngine() {
  Window = WindowSystem();
  Input = InputSystem();
  Time = TimeSystem();
  Script = ScriptSystem();
  running = false;
}

void GameEngine::add_system(std::shared_ptr<System> system) {
  system->Engine = shared_from_this();
  systems[system->name] = system;
}

void GameEngine::add_entity(std::shared_ptr<Entity> e) {
  Entities[e->name] = e;
}

std::shared_ptr<Entity> GameEngine::create_entity(std::string name) {
  std::shared_ptr<Entity> e = std::make_shared<Entity>(name);
  add_entity(e);
  return e;
}

std::shared_ptr<Entity> GameEngine::find(std::string name) {
  return Entities[name];
}

void GameEngine::message(std::string system,
                         std::shared_ptr<IMessage> message) {
  systems[system]->add_message(message);
}

void GameEngine::run() {
  this->running = true;

  // Attach Engine to standard systems
  Window.Engine = shared_from_this();
  Input.Engine = shared_from_this();
  Time.Engine = shared_from_this();
  Script.Engine = shared_from_this();

  // Initiate
  Window.init();
  Input.init();
  Time.init();
  Script.init();

  for (auto system : systems) {
    system.second->init();
  }

  // Main Game Loop

  while (running) {
    // Kill all entities marked for death
    for (auto &pair : Entities) {
      if (pair.second->destroy) {
        Entities.erase(pair.first);
      }
    }

    Window.update();
    Input.update();
    Time.update();
    Script.update();
    for (auto system : systems) {
      system.second->update();
    }
    Window.flip();
    Time.delay();
  }

  // Quit
  for (auto system : systems) {
    system.second->quit();
  }

  Script.quit();
  Time.quit();
  Input.quit();
  Window.quit();
}

void GameEngine::quit() { this->running = false; }
