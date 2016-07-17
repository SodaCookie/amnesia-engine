#include "input.h"
#include "engine.h"

InputSystem::InputSystem() : System("input") {

}

void InputSystem::init() {

}

void InputSystem::update() {
    // Look for special events
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            Engine->quit();
        }
    }

    // Capture input
    keys = SDL_GetKeyboardState(NULL);
    mods = SDL_GetModState();
    mouse.button = SDL_GetMouseState(&mouse.x, &mouse.y);
}

void InputSystem::quit() {

}

// Utility functions
// bool InputSystem::key(std::string key_) {
//
// }

bool InputSystem::key(SDL_Scancode scancode) {
    return keys[scancode];
}

bool InputSystem::mousebutton(std::string button) {
    if (button == "left") {
        return mousebutton(SDL_BUTTON_LEFT);
    }
    else if (button == "center") {
        return mousebutton(SDL_BUTTON_MIDDLE);
    }
    else if (button == "right") {
        return mousebutton(SDL_BUTTON_RIGHT);
    }
    return false;
}

bool InputSystem::mousebutton(Uint8 button) {
    return mouse.button & SDL_BUTTON(button);
}

int InputSystem::mousex() {
    return mouse.x;
}

int InputSystem::mousey() {
    return mouse.y;
}

std::pair<int, int> InputSystem::mousepos(){
    return std::pair<int, int>(mouse.x, mouse.y);
}
