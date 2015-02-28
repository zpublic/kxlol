#ifndef __MAGICITE_EFFECT_CREATE__
#define __MAGICITE_EFFECT_CREATE__

#include "MagiciteEffect.h"

class MagiciteGameObject;

class MagiciteEffectCreate : public MagiciteEffect
{
public:

    virtual void positive(MagiciteGameObject* obj)
    {
        ///> 在指定位置创建一个陷阱
    }
};

#endif //__MAGICITE_EFFECT_CREATE__