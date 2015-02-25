#ifndef __MAGICITE_EFFECT_CREATE_PITFALL__
#define __MAGICITE_EFFECT_CREATE_PITFALL__

#include "MagiciteEffectCreate.h"

class MagiciteEffectCreatePitfall : public MagiciteEffectCreate
{
public:
    virtual void positive(MagiciteGameObject* obj)
    {
        ///> 在指定位置创建一个陷阱
    }

};

#endif //__MAGICITE_EFFECT_CREATE_PITFALL__