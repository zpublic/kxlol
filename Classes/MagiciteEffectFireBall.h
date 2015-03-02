#ifndef __MAGICITE_EFFECT_FIREBALL__
#define __MAGICITE_EFFECT_FIREBALL__

#include "cocos2d.h"
#include "MagiciteEffectShoot.h"
#include "MagiciteGameMoveAble.h"

class MagiciteGamePhyLayer;

class MagiciteEffectFireBall : public MagiciteEffectShoot
{
public:

    MagiciteEffectFireBall();
   
    //MagiciteEffectShoot
    virtual void positive(MagiciteGameObject* obj);

    static MagiciteEffectFireBall* create(
        MagiciteGamePhyLayer* phyLayer, 
        MagiciteGameMoveAble::Direction dire);

    virtual bool init(
        MagiciteGamePhyLayer* phyLayer, 
        MagiciteGameMoveAble::Direction dire);

private:
    MagiciteGamePhyLayer*                           _phyLayer;
    MagiciteGameMoveAble::Direction                 _dire;
};

#endif //__MAGICITE_EFFECT_FIREBALL__