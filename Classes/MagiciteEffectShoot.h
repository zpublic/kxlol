#ifndef __MAGICITE_EFFECT_SHOOT__
#define __MAGICITE_EFFECT_SHOOT__

#include "MagiciteEffectCreate.h"

class MagiciteEffectShoot : public MagiciteEffectCreate
{
public:
    virtual void positive() 
    {
        ///> 创建一个子弹object 给个速度和方向 射出去就行了
    }

};

#endif //__MAGICITE_EFFECT_SHOOT__