#include "time.h"
#include "SDL2/SDL.h"

TimeSystem::TimeSystem() : System("time") {
    frames = 60;
}

void TimeSystem::init() {

}

void TimeSystem::update() {

}

void TimeSystem::quit() {

}

void TimeSystem::delay() {
    SDL_Delay(1000 / frames);
}
