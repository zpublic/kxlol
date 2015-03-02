#ifndef __MAGICITE_EFFECT_FIREBALL__
#define __MAGICITE_EFFECT_FIREBALL__

#include "cocos2d.h"
#include "MagiciteEffectShoot.h"

class MagiciteGamePhyLayer;

class MagiciteEffectFireBall : public MagiciteEffectShoot
{
public:

    MagiciteEffectFireBall();
   
    //MagiciteEffectShoot
    virtual void positive(MagiciteGameObject* obj);

    static MagiciteEffectFireBall* create(
        MagiciteGamePhyLayer* phyLayer);

    virtual bool init(
        MagiciteGamePhyLayer* phyLayer);

private:
    MagiciteGamePhyLayer*                           _phyLayer;
};

#endif //__MAGICITE_EFFECT_FIREBALL__