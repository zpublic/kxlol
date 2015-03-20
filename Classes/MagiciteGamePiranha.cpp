#include "MagiciteGamePiranha.h"

USING_NS_CC;

MagiciteGamePiranha::MagiciteGamePiranha()
:MagiciteGamePitfall(Prianha)
{

}

bool MagiciteGamePiranha::init()
{
    if (!MagiciteGamePitfall::initWithFile("img\\Magicite\\pitfall\\Piranha.png"))
    {
        return false;
    }
    return true;
}
