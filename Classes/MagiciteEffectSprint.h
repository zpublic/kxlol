#ifndef __MAGICITE_EFFECT_SPRINT__
#define __MAGICITE_EFFECT_SPRINT__

#include "cocos2d.h"
#include "MagiciteEffectBuffer.h"
#include "MagiciteGameMoveAbleLiving.h"

class MagiciteEffectSprint :public MagiciteEffectBuffer
{
public:
    MagiciteEffectSprint(MagiciteGameMoveAbleLiving* moveable);

    static const int sprint_speed_seed = 3;

    static const int time = 3;

    virtual void positive();

    virtual void negative();

    void step(float dTime);

private:
    MagiciteGameMoveAbleLiving*                         _moveable;
    int                                                 _old_speed;
};

#endif //__MAGICITE_EFFECT_SPRINT__