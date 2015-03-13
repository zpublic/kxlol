#include "MagiciteGameGround.h"

MagiciteGameGround::MagiciteGameGround()
:MagiciteGameObject(T_Ground)
{

}

MagiciteGameGround::~MagiciteGameGround()
{

}

bool MagiciteGameGround::init()
{
    if (!MagiciteGameObject::init())
    {
        return false;
    }
    return true;
}

bool MagiciteGameGround::initWithFile(const char* filename)
{
    if (!MagiciteGameObject::initWithFile(filename))
    {
        return false;
    }

    return true;
}

void MagiciteGameGround::onStep()
{

}