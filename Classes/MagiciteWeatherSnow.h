#ifndef __MAGICITE_WEATHER_SNOW__
#define __MAGICITE_WEATHER_SNOW__

#include "cocos2d.h"
#include "MagiciteWeather.h"
#include "MagiciteWeatherEffectSnow.h"

class MagiciteWeatherSnow : public MagiciteWeather
{
public:
    MagiciteWeatherSnow();
    
    //MagiciteWeather
    virtual MagiciteWeatherEffect* getWeatherEffect(const cocos2d::Vec2& range);
};

#endif //__MAGICITE_WEATHER_SNOW__