#ifndef __MAGICITE_GAME_FIREBALL__
#define __MAGICITE_GAME_FIREBALL__

#include "cocos2d.h"
#include "MagiciteGameAmmo.h"
#include "MagiciteGameMoveAble.h"

class MagiciteGameFireball : public MagiciteGameAmmo, public MagiciteGameMoveAble
{
public:
    MagiciteGameFireball();

    virtual void Move(Direction dire);
    virtual void Stop();
    virtual void Jump();
    virtual void JumpOver();

    virtual void initAnimation();
    virtual void startAnimation(AnimationTag);
    virtual void stopAnimation(AnimationTag);
    
    virtual bool init();

    CREATE_FUNC(MagiciteGameFireball);

protected:
    cocos2d::RepeatForever* createMoveAnimation();

    void setBodyXSpeed(float x_speed);
};

#endif //__MAGICITE_GAME_FIREBALL__