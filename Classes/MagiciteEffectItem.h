#ifndef __MAGICITE_EFFECT_ITEM__
#define __MAGICITE_EFFECT_ITEM__

#include "MagiciteItem.h"

class MagiciteEffect;

class MagiciteEffectItem : public MagiciteItem
{
public:
    MagiciteEffectItem();
    ~MagiciteEffectItem();

    //MagiciteItem
    virtual bool init();
    virtual bool initWithFile(const char* filename);

    virtual void positive(MagiciteGameObject* obj);

protected:
    void setEffect(MagiciteEffect* effect);
    MagiciteEffect*                         _effect;
};

#endif //__MAGICITE_EFFECT_ITEM__