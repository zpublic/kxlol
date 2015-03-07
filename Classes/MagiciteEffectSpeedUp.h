#ifndef __MAGICITE_EFFECT_SPEED_UP__
#define __MAGICITE_EFFECT_SPEED_UP__

#include "cocos2d.h"
#include "MagiciteEffectBuffer.h"

class MagiciteGameObject;

class MagiciteEffectSpeedUp : public MagiciteEffectBuffer
{
public:

    enum : long long { cool_down = 3000 }; //milliseconds

    MagiciteEffectSpeedUp();

    virtual void positive(MagiciteGameObject* obj);
        //MagiciteEffectValueChange.positive
        //timer-negative

    virtual void negative();
        ///> 这儿不需要做啥 交给timer来取消效果

    CREATE_FUNC(MagiciteEffectSpeedUp);
    virtual bool init();


private:
    float                                           _old_speed;
};

#endif //__MAGICITE_EFFECT_SPEED_UP__