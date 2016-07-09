#include <iostream>
#include <memory>
#include "amnesia/core/engine.h"

#include <tuple>

int main(int argc, char *argv[]) {
    std::shared_ptr<GameEngine> e = std::shared_ptr<GameEngine>(new GameEngine());
    e->run();
    return 0;
}
