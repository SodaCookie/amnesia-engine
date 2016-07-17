#ifndef _DEMO_CHARACTER_
#define _DEMO_CHARACTER_

#include "amnesia_core.h"
#include <iostream>
#include <memory>

class CharacterScript : public Script {

  void update() override { std::cout << "Hello every frame" << std::endl; }
};

#endif
