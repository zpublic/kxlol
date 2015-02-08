#pragma once
#include "MagiciteEffect.h"

class MagiciteEffectShoot : public MagiciteEffect
{
public:
    virtual void positive() 
    {
        ///> 创建一个子弹object 给个速度和方向 射出去就行了
    }

};
