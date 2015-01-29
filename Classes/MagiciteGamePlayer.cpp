#include "MagiciteGamePlayer.h"

USING_NS_CC;

MagiciteGamePlayer::MagiciteGamePlayer()
{

}

MagiciteGamePlayer::~MagiciteGamePlayer()
{

}

MagiciteGamePlayer* MagiciteGamePlayer::create(const char* filename)
{
    auto ptr = new MagiciteGamePlayer();
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
    if (!MagiciteGameLivine::initWithFile(filename))
    {
        return false;
    }
    return true;
}

