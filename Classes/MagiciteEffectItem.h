#ifndef __MAGICITE_EFFECT_ITEM__
#define __MAGICITE_EFFECT_ITEM__

#include "MagiciteItem.h"
#include "MagiciteEffect.h"

class MagiciteEffectItem : public MagiciteItem
{
public:
    MagiciteEffectItem();
    ~MagiciteEffectItem();

    virtual void positive();

protected:
    MagiciteEffect*                         _effect;
};

#endif //__MAGICITE_EFFECT_ITEM__