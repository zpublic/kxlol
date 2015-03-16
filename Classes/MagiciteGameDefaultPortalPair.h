#ifndef __MAGICITE_GAME_DEFAULT_PORTAL_PAIR__
#define __MAGICITE_GAME_DEFAULT_PORTAL_PAIR__

#include "MagiciteGamePortalPair.h"

class MagiciteGameDefaultPortalPair : public MagiciteGamePortalPair
{
public:
    MagiciteGameDefaultPortalPair();
    ~MagiciteGameDefaultPortalPair();

    virtual bool init();

    CREATE_FUNC(MagiciteGameDefaultPortalPair);

protected:
    virtual MagiciteGamePortal* getPortalA();
    virtual MagiciteGamePortal* getPortalB();
};

#endif //__MAGICITE_GAME_DEFAULT_PORTAL_PAIR__