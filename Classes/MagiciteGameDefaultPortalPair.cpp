#include "MagiciteGameDefaultPortalPair.h"
#include "MagiciteGameDefaultPortal.h"

MagiciteGameDefaultPortalPair::MagiciteGameDefaultPortalPair()
{

}

MagiciteGameDefaultPortalPair::~MagiciteGameDefaultPortalPair()
{

}

bool MagiciteGameDefaultPortalPair::init()
{
    if (!MagiciteGamePortalPair::init())
    {
        return false;
    }

    return true;
}

MagiciteGamePortal* MagiciteGameDefaultPortalPair::getPortalA()
{
    return MagiciteGameDefaultPortal::create();
}

MagiciteGamePortal* MagiciteGameDefaultPortalPair::getPortalB()
{
    return MagiciteGameDefaultPortal::create();
}
