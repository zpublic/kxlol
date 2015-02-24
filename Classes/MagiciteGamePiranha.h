#ifndef __MAGICITE_GAME_PIRANHA__
#define __MAGICITE_GAME_PIRANHA__

#include "cocos2d.h"
#include "MagiciteGameLiving.h"

class MagiciteGamePiranha : public MagiciteGameLiving
{
public:
    MagiciteGamePiranha();

    virtual bool init();
    
    CREATE_FUNC(MagiciteGamePiranha);
};

#endif //__MAGICITE_GAME_PIRANHA__
