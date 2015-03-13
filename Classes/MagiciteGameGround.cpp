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
