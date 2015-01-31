#include "MagiciteGamePlayer.h"

USING_NS_CC;

MagiciteGamePlayer::MagiciteGamePlayer()
{
    _LivingType = MagiciteGameLiving::T_Player;
}

MagiciteGamePlayer::~MagiciteGamePlayer()
{

}

MagiciteGamePlayer* MagiciteGamePlayer::create(const char* filename)
{
    auto ptr = new(std::nothrow) MagiciteGamePlayer();
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

bool MagiciteGamePlayer::initWithFile(const char* filename)
{
    if (!MagiciteGameLiving::initWithFile(filename))
    {
        return false;
    }
    return true;
}

