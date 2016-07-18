#include "amnesia_core.h"
#include "scripts/character_script.h"
#include <memory>

#ifdef main
#undef main
#endif /* main */

void init() {
  Engine->Window.width = 800;
  Engine->Window.height = 600;

  Engine->add_system(std::make_shared<ScriptSystem>());

  std::shared_ptr<Entity> e1 = Engine->create_entity("test");
  e1->add_component<CharacterScript>();
}

int main(int argc, char *argv[]) {
  init();
  Engine->run();
}
