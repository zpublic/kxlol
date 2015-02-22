#ifndef __MAGICITE_GAME_INCUBATOR__
#define __MAGICITE_GAME_INCUBATOR__

#include "cocos2d.h"
#include "MagiciteGamePet.h"

class MagiciteGameIncubator : public MagiciteGamePet
{
public:
    MagiciteGameIncubator();

    virtual bool init();

    CREATE_FUNC(MagiciteGameIncubator);

};

#endif //__MAGICITE_GAME_INCUBATOR__