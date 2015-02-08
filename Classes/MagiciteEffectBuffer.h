#pragma once
#include "MagiciteEffect.h"

///> 这是一个buffer，改变某些属性后，定时到齐后改回来
class MagiciteEffectBuffer : public MagiciteEffect
{
public:
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
