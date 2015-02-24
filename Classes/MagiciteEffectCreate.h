#ifndef __MAGICITE_EFFECT_CREATE__
#define __MAGICITE_EFFECT_CREATE__

#include "MagiciteEffect.h"
#include "MagiciteGameObject.h"

class MagiciteEffectCreate : public MagiciteEffect
{
public:
    typedef MagiciteGameObject::_entityCategory Category;

    virtual void positive()
    {
        ///> 在指定位置创建一个陷阱
    }
};

#endif //__MAGICITE_EFFECT_CREATE__