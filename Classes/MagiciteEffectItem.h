#ifndef __MAGICITE_EFFECT_ITEM__
#define __MAGICITE_EFFECT_ITEM__

#include "MagiciteItem.h"
#include "MagiciteEffect.h"
#include "MagiciteGameObject.h"

class MagiciteEffectItem : public MagiciteItem
{
public:
    MagiciteEffectItem();
    ~MagiciteEffectItem();

    virtual void positive(MagiciteGameObject* obj);

protected:
    MagiciteEffect*                         _effect;
};

#endif //__MAGICITE_EFFECT_ITEM__