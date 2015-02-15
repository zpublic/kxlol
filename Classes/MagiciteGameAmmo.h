#ifndef __MAGICITE_GAME_AMMO__
#define __MAGICITE_GAME_AMMO__

#include "cocos2d.h"
#include "MagiciteGameObject.h"
#include "MagiciteGameMoveAble.h"

class MagiciteGameAmmo : public MagiciteGameObject, public MagiciteGameMoveAble
{
public:
    MagiciteGameAmmo();

    virtual bool init();
    virtual bool initWithFile(const char* filename);

};

#endif //__MAGICITE_GAME_AMMO__