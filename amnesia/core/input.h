#ifndef _AMNESIA_INPUTSYSTEM_HEADER_
#define _AMNESIA_INPUTSYSTEM_HEADER_

#include "system.h"

class InputSystem : public System {

public:

    InputSystem();

    virtual void init() override;

    virtual void update() override;

    virtual void quit() override;

};

#endif