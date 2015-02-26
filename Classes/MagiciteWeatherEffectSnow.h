#ifndef __MAGICITE_WEATHER_EFFECT_SNOW__
#define __MAGICITE_WEATHER_EFFECT_SNOW__

#include "MagiciteWeatherEffect.h"

class MagiciteWeatherEffectSnow : public MagiciteWeatherEffect
{
public:
    MagiciteWeatherEffectSnow(const cocos2d::Vec2& range);

    virtual void positive(cocos2d::Layer* layer);
private:
    cocos2d::Vec2                   _range;
};

#endif //__MAGICITE_WEATHER_EFFECT_SNOW__