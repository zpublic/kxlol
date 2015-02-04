#include "MagiciteGamePitfall.h"

USING_NS_CC;

MagiciteGamePitfall::MagiciteGamePitfall()
{
    _SpriteType = MagiciteGamePhySprite::T_Pitfall;
}

MagiciteGamePitfall::~MagiciteGamePitfall()
{

}

bool MagiciteGamePitfall::initWithFile(const char* filename, bool is_turn_on)
{
    if (!MagiciteGamePhySprite::initWithFile(filename))
    {
        return false;
    }
    _is_pitfall_on = is_turn_on;
    return true;
}

MagiciteGamePitfall* MagiciteGamePitfall::create(const char* filename, bool is_turn_on)
{
    auto ptr = new MagiciteGamePitfall();
    if (ptr && ptr->initWithFile(filename, is_turn_on))
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
}