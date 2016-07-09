#ifndef _AMNESIA_INPUTSYSTEM_HEADER_
#define _AMNESIA_INPUTSYSTEM_HEADER_

#include <utility>
#include "system.h"
#include "SDL2/SDL.h"

struct MouseState {
    int x;
    int y;
    Uint32 button;
};

class InputSystem : public System {

public:

    InputSystem();

    virtual void init() override;

    virtual void update() override;

    virtual void quit() override;

    // Utility functions
    // bool key(std::string key_);

    bool key(SDL_Scancode scancode);

    bool mod(std::string mod_) {
        if (mod_ == "shift") {
            return mod(KMOD_SHIFT);
        }
        else if (mod_ == "ctrl") {
            return mod(KMOD_CTRL);
        }
        else if (mod_ == "alt") {
            return mod(KMOD_ALT);
        }
        return false;
    }

    template <typename T>
    bool mod(T mod_) {
        return mods & mod_;
    }

    template <typename T, typename ...Ts>
    bool mod(T mod_, Ts... mods_) {
        return (mods & mod_) && mod(mods_...);
    }

    bool mousebutton(std::string button);

    bool mousebutton(Uint8 button);

    int mousex();

    int mousey();

    std::pair<int, int> mousepos();

private:
    const Uint8 *keys;
    SDL_Keymod mods;
    MouseState mouse;

};

#endif
