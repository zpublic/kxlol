#include "MagiciteGamePitfallClamp.h"

USING_NS_CC;

MagiciteGamePitfallClamp::MagiciteGamePitfallClamp()
{

}

MagiciteGamePitfallClamp::~MagiciteGamePitfallClamp()
{

}

bool MagiciteGamePitfallClamp::init()
{
    if (!MagiciteGamePitfall::initWithFile("CloseSelected.png"))
    {
        return false;
    }
    return true;
}

MagiciteGamePitfallClamp* MagiciteGamePitfallClamp::create()
{
    auto ptr = new MagiciteGamePitfallClamp();
    if (ptr && ptr->init())
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