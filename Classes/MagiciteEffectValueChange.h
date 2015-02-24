#ifndef __MAGICITE__EFFECT_VALUE_CHANGE__
#define __MAGICITE__EFFECT_VALUE_CHANGE__

#include "MagiciteEffect.h"

class MagiciteEffectValueChange : public MagiciteEffect
{
public:
    virtual void positive() 
    {
        ///> 比如在这里加三点力量
    }

    virtual void negative() 
    {
        ///> 那么这儿是减三点力量
    }

};

#endif //__MAGICITE__EFFECT_VALUE_CHANGE__