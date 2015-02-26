#include "MagiciteWeatherSnow.h"

USING_NS_CC;

MagiciteWeatherSnow::MagiciteWeatherSnow()
{

}

MagiciteWeatherEffect* MagiciteWeatherSnow::getWeatherEffect(const Vec2& range)
{
    return new MagiciteWeatherEffectSnow(range);
}