#ifndef __MAGICITE_WEATHER__
#define __MAGICITE_WEATHER__

#include "cocos2d.h"

class MagiciteWeatherEffect;

class MagiciteWeather
{
public:

    virtual MagiciteWeatherEffect* getWeatherEffect(const cocos2d::Vec2& range) = 0;
};

#endif //__MAGICITE_WEATHER__