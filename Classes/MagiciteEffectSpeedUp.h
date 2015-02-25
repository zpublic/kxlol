#ifndef __MAGICITE_EFFECT_SPEED_UP__
#define __MAGICITE_EFFECT_SPEED_UP__

#include "cocos2d.h"
#include "MagiciteGameMoveAbleLiving.h"
#include "MagiciteEffectBuffer.h"

class MagiciteEffectSpeedUp : public MagiciteEffectBuffer
{
public:
    MagiciteEffectSpeedUp();

    virtual void positive(MagiciteGameObject* obj);
        //MagiciteEffectValueChange.positive
        //timer-negative

    virtual void negative();
        ///> 这儿不需要做啥 交给timer来取消效果

    static MagiciteEffectSpeedUp* create();
    virtual bool init();


private:
    float                                           _old_speed;
};

#endif //__MAGICITE_EFFECT_SPEED_UP__