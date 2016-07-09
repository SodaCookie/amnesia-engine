#include "input.h"
#include "engine.h"
#include "SDL2/SDL.h"

InputSystem::InputSystem() : System("time") {

}

void InputSystem::init() {

}

void InputSystem::update() {
    SDL_PumpEvents();
    if (SDL_HasEvent(SDL_QUIT)) {
        Engine->quit();
    }
}

void InputSystem::quit() {

}
