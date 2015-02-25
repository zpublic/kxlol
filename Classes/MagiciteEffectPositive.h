#ifndef __MAGICITE_EFFECT_POSITIVE__
#define __MAGICITE_EFFECT_POSITIVE__
#include "MagiciteEffect.h"

///> 这是一个永久增强
class MagiciteEffectPositive : public MagiciteEffect
{
public:
    virtual void positive(MagiciteGameObject* obj)
    {
        //MagiciteEffectValueChange.positive
    }

    virtual void negative() 
    {
        // 这儿不干啥
    }

};

#endif //__MAGICITE_EFFECT_POSITIVE__