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
    virtual void initParticle() = 0;

protected:
    virtual void setBodyXSpeed(float x_speed);
    virtual void setBodyYSpeed(float y_speed);
};

#endif //__MAGICITE_GAME_AMMO__