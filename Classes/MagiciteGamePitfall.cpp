#include "MagiciteGamePitfall.h"

USING_NS_CC;

MagiciteGamePitfall::MagiciteGamePitfall()
:_is_pitfall_on(true)
{
    _SpriteType = MagiciteGamePhySprite::T_Pitfall;
}

MagiciteGamePitfall::~MagiciteGamePitfall()
{

}

bool MagiciteGamePitfall::initWithFile(const char* filename)
{
    if (!MagiciteGamePhySprite::initWithFile(filename))
    {
        return false;
    }

    return true;
}

MagiciteGamePitfall* MagiciteGamePitfall::create(const char* filename)
{
    auto ptr = new MagiciteGamePitfall();
    if (ptr && ptr->initWithFile(filename))
    {
        ptr->autorelease();
        return ptr;
    }
    else
    {
        CC_SAFE_DELETE(ptr);
        return nullptr;
    }
}

bool MagiciteGamePitfall::getPitFallState()
{
    return _is_pitfall_on;
}

void MagiciteGamePitfall::setPitFallState(bool is_turn_on)
{
    _is_pitfall_on = is_turn_on;
    if (getBody() != nullptr)
    {
        getBody()->SetActive(is_turn_on);
    }
}