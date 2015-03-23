#ifndef __MAGICITE_EFFECT_ACID__
#define __MAGICITE_EFFECT_ACID__

#include "cocos2d.h"
#include "MagiciteEffectShoot.h"

class MagiciteEffectAcid : public MagiciteEffectShoot
{
public:

    MagiciteEffectAcid();

    virtual void positive(MagiciteGameObject* obj);

    CREATE_FUNC(MagiciteEffectAcid);

    virtual bool init();

};

#endif //__MAGICITE_EFFECT_ACID__