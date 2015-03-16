#include "MagiciteGameMeteorite.h"

USING_NS_CC;

MagiciteGameMeteorite::MagiciteGameMeteorite()
{

}

MagiciteGameMeteorite::~MagiciteGameMeteorite()
{

}

bool MagiciteGameMeteorite::init()
{
    if (!MagiciteGameMovePitfall::initWithFile("img\\Magicite\\pitfall\\stone.png"))
    {
        return false;
    }

    auto flame = ParticleFire::create();
    flame->setLife(1.0f);
    flame->setLifeVar(0.25f);
    flame->setPosition(this->getPosition());
    this->addChild(flame);

    setSpeed(meteorite_speed);

    return true;
}