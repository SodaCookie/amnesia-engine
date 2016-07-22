#include "renderer.h"

void Renderer::init() {
  std::static_pointer_cast<ScriptSystem>(Engine->get_system("script"))
      ->add_script(shared_from_this());
}
