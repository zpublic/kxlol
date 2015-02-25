#ifndef __MAGICITE_EFFECT_JUMPHIGH__
#define __MAGICITE_EFFECT_JUMPHIGH__

#include "cocos2d.h"
#include "MagiciteEffectBuffer.h"
#include "MagiciteGameMoveAbleLiving.h"

class MagiciteEffectJumpHigh : public MagiciteEffectBuffer
{
public:
    MagiciteEffectJumpHigh();

    virtual void positive(MagiciteGameObject* obj);
    //MagiciteEffectValueChange.positive
    //timer-negative

    virtual void negative();
    ///> 这儿不需要做啥 交给timer来取消效果

    static MagiciteEffectJumpHigh* create();
    virtual bool init();

};

#endif //__MAGICITE_EFFECT_JUMPHIGH__