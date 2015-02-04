#include "MagiciteGamePitfallClamp.h"

USING_NS_CC;

MagiciteGamePitfallClamp::MagiciteGamePitfallClamp()
{

}

MagiciteGamePitfallClamp::~MagiciteGamePitfallClamp()
{

}

bool MagiciteGamePitfallClamp::init(bool is_turn_on)
{
    if (!MagiciteGamePitfall::initWithFile("CloseSelected.png", is_turn_on))
    {
        return false;
    }
    return true;
}

MagiciteGamePitfallClamp* MagiciteGamePitfallClamp::create(bool is_turn_on)
{
    auto ptr = new MagiciteGamePitfallClamp();
    if (ptr && ptr->init(is_turn_on))
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