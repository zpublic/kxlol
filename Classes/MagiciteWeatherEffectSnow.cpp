#include "MagiciteWeatherEffectSnow.h"

USING_NS_CC;

MagiciteWeatherEffectSnow::MagiciteWeatherEffectSnow(const cocos2d::Vec2& range)
:_range(range)
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