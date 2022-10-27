// 
// 
// 

#include "StatusIndicator.h"

StatusIndicator::StatusIndicator(Adafruit_DotStar* ds)
{
    _ds = ds;
    state = Status_State::STARTING;
    color_normal = _ds->gamma32(_ds->Color(87, 148, 255));
    color_err = _ds->gamma32(_ds->Color(175, 6, 6));
    color_busy = _ds->gamma32(_ds->Color(202, 213, 235));
    br_max = 30;
    br_min = 4;
    timer = 0;
    going_up = true;
    color = true;
};

void StatusIndicator::begin()
{
    brightness = br_min;
    timer = millis();
    _ds->begin();
    _ds->setBrightness(2);
    _ds->show();
}

void StatusIndicator::update()
{
    switch (state)
    {
    case NORMAL:
        _ds->setPixelColor(0, color_normal);
        _ds->setBrightness(br_min);
        _ds->show();
        break;

    case WARN:
        _ds->setPixelColor(0, color_warn);
        _ds->show();
        break;

    case ERR:
        _ds->setPixelColor(0, color_err);
        _ds->show();
        break;

    case STARTING:
        if (millis() - timer > STARTING_CYCLE)
        {
            timer = millis();
            brightness = going_up ? brightness + 1 : brightness - 1;
            if (brightness >= br_max)
            {
                going_up = false;
            }
            if (brightness <= br_min)
            {
                going_up = true;
            }
        }
        _ds->setPixelColor(0, color_busy);
        _ds->setBrightness(brightness);
        _ds->show();
        break;

    case ADOPTING:
        if (millis() - timer > ADOPTION_CYCLE)
        {
            timer = millis();
            brightness = going_up ? brightness + 1 : brightness - 1;
            if (brightness >= br_max)
            {
                going_up = false;
            }
            if (brightness <= br_min)
            {
                going_up = true;
            }
        }
        _ds->setPixelColor(0, color_normal);
        _ds->setBrightness(brightness);
        _ds->show();
        break;

    case UPDATING:
        if (millis() - timer > UPDATING_CYCLE)
        {
            timer = millis();
            color = !color;
        }
        _ds->setPixelColor(0, color ? color_busy : color_normal);
        _ds->setBrightness(br_max);
        _ds->show();
        break;

    default:
        break;
    }
}

void StatusIndicator::set(Status_State s)
{
    state = s;
}


