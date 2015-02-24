#ifndef __MAGICITE_EFFECT_BUFER__
#define __MAGICITE_EFFECT_BUFER__

#include "MagiciteEffect.h"
#include "MagiciteGameTagManager.h"

///> 这是一个buffer，改变某些属性后，定时到齐后改回来
class MagiciteEffectBuffer : public MagiciteEffect
{
public:

    enum Buff_Type : int
    {
        Speed_Up = MagiciteGameTagManager::Speed_Up_Tag,
        Jump_High = MagiciteGameTagManager::Jump_High_Tag,
        Sprint_Tag = MagiciteGameTagManager::Sprint_Tag,
    };

    virtual void positive() 
    {
        //MagiciteEffectValueChange.positive
        //timer-negative
    }

    virtual void negative() 
    {
        ///> 这儿不需要做啥 交给timer来取消效果
    }

};

#endif //__MAGICITE_EFFECT_BUFER__