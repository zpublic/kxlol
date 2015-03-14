#include "MagiciteGamePortalPair.h"
#include "MagiciteGamePortal.h"

USING_NS_CC;

MagiciteGamePortalPair::MagiciteGamePortalPair()
{

}

MagiciteGamePortalPair::~MagiciteGamePortalPair()
{
    _portalA->release();
    _portalB->release();
}

bool MagiciteGamePortalPair::init()
{
    if (!Node::init())
    {
        return false;
    }

    _portalA = this->getPortalA();
    _portalB = this->getPortalB();
    if (_portalA == nullptr || _portalB == nullptr)
    {
        return false;
    }

    _portalA->retain();
    _portalB->retain();

    return true;
}

MagiciteGamePortal* MagiciteGamePortalPair::PortalA()
{
    return _portalA;
}

MagiciteGamePortal* MagiciteGamePortalPair::PortalB()
{
    return _portalB;
}