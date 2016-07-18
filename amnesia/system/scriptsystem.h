#ifndef _AMNESIA_SCRIPTSYSTEM_HEADER_
#define _AMNESIA_SCRIPTSYSTEM_HEADER_

#include "../classes/script.h"
#include "../core/system.h"
#include <list>
#include <memory>

class ScriptSystem : public System {

public:
  ScriptSystem();

  virtual void init() override;

  virtual void update() override;

  virtual void quit() override;

  void add_script(std::shared_ptr<Script> script);

private:
  std::list<std::weak_ptr<Script>> scripts;
};

#endif
