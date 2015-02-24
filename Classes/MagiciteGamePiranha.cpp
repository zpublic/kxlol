#include "MagiciteGamePiranha.h"

USING_NS_CC;

MagiciteGamePiranha::MagiciteGamePiranha()
:MagiciteGameLiving(NormalLiving,Piranha)
{

}

bool MagiciteGamePiranha::init()
{
    if (!MagiciteGameLiving::initWithFile("CloseSelected"))
    {
        return false;
    }
    return true;
}
