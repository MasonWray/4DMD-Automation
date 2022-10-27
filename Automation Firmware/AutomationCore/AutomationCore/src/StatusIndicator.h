#ifndef _StatusIndicator_h
#define _StatusIndicator_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <Adafruit_DotStar.h>

#define STARTING_CYCLE 30
#define ADOPTION_CYCLE 15
#define UPDATING_CYCLE 150

class StatusIndicator
{
public:
    StatusIndicator(Adafruit_DotStar* ds);
    enum Status_State
    {
        NORMAL,
        WARN,
        ERR,
        STARTING,
        ADOPTING,
        UPDATING
    };
    void begin();
    void update();
    void set(Status_State s);

private:
    Adafruit_DotStar* _ds;
    Status_State state;
    uint32_t color_normal;
    uint32_t color_warn;
    uint32_t color_err;
    uint32_t color_busy;
    uint8_t br_max;
    uint8_t br_min;
    uint32_t timer;
    uint16_t brightness;
    bool going_up;
    bool color;
};


#endif

