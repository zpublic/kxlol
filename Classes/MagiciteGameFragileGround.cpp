#include "MagiciteGameFragileGround.h"

USING_NS_CC;

MagiciteGameFragileGround::MagiciteGameFragileGround()
:_is_destroy(false)
{

}

MagiciteGameFragileGround::~MagiciteGameFragileGround()
{

}

bool MagiciteGameFragileGround::init()
{
    if (!MagiciteGameGround::initWithFile("img\\Magicite\\map\\fragile_ground.png"))
    {
        return false;
    }

    return true;
}

bool MagiciteGameFragileGround::initWithFile(const char* filename)
{
    if (!MagiciteGameGround::initWithFile(filename))
    {
        return false;
    }

    return true;
}

void MagiciteGameFragileGround::onStep()
{
    if (!_is_destroy)
    {
        this->runAction(Sequence::create(DelayTime::create(1.5f), CallFunc::create([this](){
            this->Dead();
        }), nullptr));
        _is_destroy = true;
    }
}