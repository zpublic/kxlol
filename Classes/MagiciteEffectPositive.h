#pragma once
#include "MagiciteEffect.h"

///> 这是一个永久增强
class MagiciteEffectPositive : public MagiciteEffect
{
public:
    virtual void positive() 
    {
        //MagiciteEffectValueChange.positive
    }

    virtual void negative() 
    {
        // 这儿不干啥
    }

};
