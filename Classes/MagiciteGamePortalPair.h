#ifndef __MAGICITE_GAME_PROTAL_PAIR__
#define __MAGICITE_GAME_PROTAL_PAIR__

#include "cocos2d.h"

class MagiciteGamePortal;

class MagiciteGamePortalPair : public cocos2d::Node
{
public:
    MagiciteGamePortalPair();
    ~MagiciteGamePortalPair();

    virtual bool init();

    MagiciteGamePortal* PortalA();
    MagiciteGamePortal* PortalB();

protected:
    virtual MagiciteGamePortal* getPortalA() = 0;
    virtual MagiciteGamePortal* getPortalB() = 0;

private:
    MagiciteGamePortal*         _portalA;
    MagiciteGamePortal*         _portalB;
};

#endif //__MAGICITE_GAME_PROTAL_PAIR__