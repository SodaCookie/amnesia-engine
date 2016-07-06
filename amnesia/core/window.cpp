#include "window.h"

WindowSystem::WindowSystem() : System("window") {
}

void WindowSystem::init() {
    display = SDL_CreateWindow(
        title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height, SDL_WINDOW_SHOWN);
    surface = SDL_GetWindowSurface(display);
}

void WindowSystem::update() {
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));
}

void WindowSystem::quit() {
    SDL_DestroyWindow(display);
    SDL_FreeSurface(surface);
}

void WindowSystem::flip() {
    SDL_UpdateWindowSurface(display);
}