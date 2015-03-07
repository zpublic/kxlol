#ifndef __MAGICITE_EFFECT_ACID__
#define __MAGICITE_EFFECT_ACID__

#include "cocos2d.h"
#include "MagiciteEffectShoot.h"

class MagiciteGamePhyLayer;

class MagiciteEffectAcid : public MagiciteEffectShoot
{
public:

    enum : int { cool_down = 3 };

    MagiciteEffectAcid();

    virtual void positive(MagiciteGameObject* obj);

    static MagiciteEffectAcid* create(MagiciteGamePhyLayer* phyLayer);

    virtual bool init(MagiciteGamePhyLayer* phyLayer);

private:
    MagiciteGamePhyLayer*                           _phyLayer;
};

#endif //__MAGICITE_EFFECT_ACID__