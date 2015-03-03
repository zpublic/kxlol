#include "MagiciteWeatherEffectSnow.h"

USING_NS_CC;

MagiciteWeatherEffectSnow::MagiciteWeatherEffectSnow()
{

}


void MagiciteWeatherEffectSnow::positive(cocos2d::Layer* layer)
{
    auto snow = ParticleSnow::create();
    snow->setTexture(Director::getInstance()->getTextureCache()->addImage("img\\Magicite\\Particle\\snow.png"));

    snow->setDuration(-1);
    snow->setGravity(Vec2(0.0f, -80.0f));

    snow->setAngle(90.0f);
    snow->setAngleVar(360.0f);
    snow->setPosition(_range.x / 2, _range.y);
    snow->setPosVar(Vec2(_range.x / 2, 0));

    snow->setStartSpin(30);
    snow->setStartSpinVar(60);
    snow->setEndSpin(60);
    snow->setEndSpinVar(60);

    snow->setEmissionRate(6);

    layer->addChild(snow);
}

bool MagiciteWeatherEffectSnow::init(const cocos2d::Vec2& range)
{
    _range = range;

    return true;
}

MagiciteWeatherEffectSnow* MagiciteWeatherEffectSnow::create(const cocos2d::Vec2& range)
{
    auto ptr = new MagiciteWeatherEffectSnow();
    if (ptr && ptr->init(range))
    {
        return ptr;
    }
    else
    {
        CC_SAFE_DELETE(ptr);
        return nullptr;
    }
}