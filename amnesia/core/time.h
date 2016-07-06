#ifndef _AMNESIA_TIMESYSTEM_HEADER_
#define _AMNESIA_TIMESYSTEM_HEADER_

#include "system.h"

class TimeSystem : public System {

public:

    double delta;

    TimeSystem();

    virtual void init() override;

    virtual void update() override;

    virtual void quit() override;

};

#endif