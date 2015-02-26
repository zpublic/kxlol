#ifndef __MAGICITE_EFFECT_FIREBALL__
#define __MAGICITE_EFFECT_FIREBALL__

#include "cocos2d.h"
#include "MagiciteEffectShoot.h"
#include "MagiciteGameFireball.h"
#include "MagiciteGamePhyLayer.h"
#include "MagiciteGaemFactoryMethod.h"

class MagiciteEffectFireBall : public MagiciteEffectShoot
{
public:

    MagiciteEffectFireBall();
   
    //MagiciteEffectShoot
    virtual void positive(MagiciteGameObject* obj);

    static MagiciteEffectFireBall* create(
        const cocos2d::Vec2& pos, 
        MagiciteGamePhyLayer* phyLayer, 
        MagiciteGameMoveAble::Direction dire);

    virtual bool init(
        const cocos2d::Vec2& pos, 
        MagiciteGamePhyLayer* phyLayer, 
        MagiciteGameMoveAble::Direction dire);

private:
    cocos2d::Vec2                                   _pos;
    MagiciteGamePhyLayer*                           _phyLayer;
    MagiciteGameMoveAble::Direction                 _dire;
};

#endif //__MAGICITE_EFFECT_FIREBALL__