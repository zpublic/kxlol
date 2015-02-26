#ifndef __MAGICITE_WEATHER_EFFECT__
#define __MAGICITE_WEATHER_EFFECT__

#include "cocos2d.h"

class MagiciteWeatherEffect
{
public:

    virtual void positive(cocos2d::Layer* layer) = 0;

};

#endif //__MAGICITE_WEATHER_EFFECT__