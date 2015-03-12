#include "MagiciteGameMeteorite.h"

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

    setSpeed(meteorite_speed);

    return true;
}