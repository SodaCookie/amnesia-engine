#include "amnesia_core.h"
#include "scripts/character_script.h"
#include <memory>

#ifdef main
#undef main
#endif /* main */

void init() {
  Engine->Window.width = 800;
  Engine->Window.height = 600;

  std::shared_ptr<Entity> e1 = Engine->create_entity("test");
  auto script = std::shared_ptr<CharacterScript>(new CharacterScript());
  e1->add_script(script);
}

int main(int argc, char *argv[]) {
  init();
  Engine->run();
}
