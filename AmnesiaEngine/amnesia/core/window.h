#ifndef _AMNESIA_WINDOWSYSTEM_HEADER_
#define _AMNESIA_WINDOWSYSTEM_HEADER_

#include "system.h"
#include "SDL2/SDL.h"
#include <memory>

class WindowSystem : public System {

public:

    SDL_Window *display;
    SDL_Surface *surface;
    std::string title;
    int width = 640;
    int height = 480;

    WindowSystem();

    virtual void init() override;

    virtual void update() override;

    virtual void quit() override;

    void flip();
};

#endif