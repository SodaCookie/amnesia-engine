#include "scriptsystem.h"

ScriptSystem::ScriptSystem() : System("script") {}

void ScriptSystem::init() {}

void ScriptSystem::update() {
  for (auto it = scripts.begin(); it != scripts.end(); it++) {
    if (auto script = it->lock()) {
      script->update();
    } else {
      it = scripts.erase(it);
    }
  }
}

void ScriptSystem::quit() {}

#include <iostream>
void ScriptSystem::add_script(std::shared_ptr<Script> script) {
  scripts.push_back(std::weak_ptr<Script>(script));
}
