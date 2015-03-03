#ifndef __MAGICITE_WEATHER_SNOW__
#define __MAGICITE_WEATHER_SNOW__

#include "cocos2d.h"
#include "MagiciteWeather.h"

class MagiciteWeatherEffect;

class MagiciteWeatherSnow : public MagiciteWeather
{
public:
    MagiciteWeatherSnow();
    
    //MagiciteWeather
    virtual MagiciteWeatherEffect* getWeatherEffect(const cocos2d::Vec2& range);

    virtual bool init();
    
    static MagiciteWeatherSnow* create();
};

#endif //__MAGICITE_WEATHER_SNOW__