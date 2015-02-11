#ifndef __MAGICITE_GAME_AMMO__
#define __MAGICITE_GAME_AMMO__

#include "cocos2d.h"
#include "MagiciteGameObject.h"

class MagiciteGameAmmo : public MagiciteGameObject
{
public:
    MagiciteGameAmmo();

    virtual bool init();
    virtual bool initWithFile(const char* filename);

    CREATE_FUNC(MagiciteGameAmmo);
    static MagiciteGameAmmo* create(const char* filename);

};

#endif //__MAGICITE_GAME_AMMO__