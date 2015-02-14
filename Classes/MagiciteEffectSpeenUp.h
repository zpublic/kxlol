#ifndef __MAGICITE_GAME_EFFECT_SPEED_UP__
#define __MAGICITE_GAME_EFFECT_SPEED_UP__

#include "cocos2d.h"
#include "MagiciteGameMoveAbleLiving.h"
#include "MagiciteEffectBuffer.h"

class MagiciteEffectSpeenUp : public MagiciteEffectBuffer
{
public:
    MagiciteEffectSpeenUp(MagiciteGameMoveAbleLiving* moveable);

    virtual void positive();
        //MagiciteEffectValueChange.positive
        //timer-negative

    virtual void negative();
        ///> 这儿不需要做啥 交给timer来取消效果
private:
    MagiciteGameMoveAbleLiving*                     _moveable;
};

#endif //__MAGICITE_GAME_EFFECT_SPEED_UP__