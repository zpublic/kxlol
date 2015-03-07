#ifndef __MAGICITE_EFFECT_SPRINT__
#define __MAGICITE_EFFECT_SPRINT__

#include "cocos2d.h"
#include "MagiciteEffectBuffer.h"

class MagiciteEffectSprint :public MagiciteEffectBuffer
{
public:

    enum : long long { cool_down = 3 };

    MagiciteEffectSprint();

    static const int sprint_speed_seed = 3;

    static const int time = 1;

    virtual void positive(MagiciteGameObject* obj);

    virtual void negative();

    CREATE_FUNC(MagiciteEffectSprint);
    virtual bool init();

private:
    float                                               _base_sprint_speed;
    float                                               _step_speed;
};

#endif //__MAGICITE_EFFECT_SPRINT__