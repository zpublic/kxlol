#include "MagiciteWeatherEffectSnow.h"
#include "MagiciteWeatherSnow.h"
#include "MagiciteWeatherEffect.h"

USING_NS_CC;

MagiciteWeatherSnow::MagiciteWeatherSnow()
{

}

MagiciteWeatherEffect* MagiciteWeatherSnow::getWeatherEffect(const Vec2& range)
{
    return MagiciteWeatherEffectSnow::create(range);
}

bool MagiciteWeatherSnow::init()
{
    return true;
}

MagiciteWeatherSnow* MagiciteWeatherSnow::create()
{
    auto ptr = new MagiciteWeatherSnow();
    if (ptr && ptr->init())
    {
        return ptr;
    }
    else
    {
        CC_SAFE_DELETE(ptr);
        return nullptr;
    }
}