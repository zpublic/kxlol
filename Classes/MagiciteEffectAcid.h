#ifndef __MAGICITE_EFFECT_ACID__
#define __MAGICITE_EFFECT_ACID__

#include "cocos2d.h"
#include "MagiciteEffectShoot.h"

class MagiciteGamePhyLayer;

class MagiciteEffectAcid : public MagiciteEffectShoot
{
public:

    enum : long long { cool_down = 1000 }; //milliseconds

    MagiciteEffectAcid();

    virtual void positive(MagiciteGameObject* obj);

    static MagiciteEffectAcid* create(MagiciteGamePhyLayer* phyLayer);

    virtual bool init(MagiciteGamePhyLayer* phyLayer);

private:
    MagiciteGamePhyLayer*                           _phyLayer;
};

#endif //__MAGICITE_EFFECT_ACID__