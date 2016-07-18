#include "script.h"
#include "../core/engine.h"
#include "../system/scriptsystem.h"

void Script::init() {
  std::static_pointer_cast<ScriptSystem>(Engine->get_system("script"))
      ->add_script(shared_from_this());
}
