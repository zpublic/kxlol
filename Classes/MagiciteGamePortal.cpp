#include "MagiciteGamePortal.h"

MagiciteGamePortal::MagiciteGamePortal()
:MagiciteGameObject(T_Portal)
{

}

MagiciteGamePortal::~MagiciteGamePortal()
{

}

bool MagiciteGamePortal::init()
{
    if (!MagiciteGameObject::init())
    {
        return false;
    }

    return true;
}

bool MagiciteGamePortal:: initWithFile(const char* filename)
{
    if (!MagiciteGameObject::initWithFile(filename))
    {
        return false;
    }

    return true;
}

MagiciteGamePortal* MagiciteGamePortal::getPair()
{
    return _pair;
}

void MagiciteGamePortal::setPair(MagiciteGamePortal* pair)
{
    _pair = pair;
}