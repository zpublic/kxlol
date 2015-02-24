#ifndef __MAGICITE_EFFECT_CREATE_FRIEND__
#define __MAGICITE_EFFECT_CREATE_FRIEND__

#include "cocos2d.h"
#include "MagiciteEffectCreate.h"
#include "MagiciteGamePhyLayer.h"
#include "MagiciteGaemFactoryMethod.h"

class MagiciteEffectCreateFriend : public MagiciteEffectCreate
{
public:

    typedef MagiciteGaemFactoryMethod::LivingType LivingType;

    MagiciteEffectCreateFriend(
        const cocos2d::Vec2& pos, 
        MagiciteGamePhyLayer* phyLayer, 
        MagiciteGameMoveAble::Direction dire, 
        LivingType type);

    //MagiciteEffectCreate
    virtual void positive();

private:
    cocos2d::Vec2                               _pos;
    MagiciteGamePhyLayer*                       _phyLayer;
    MagiciteGameMoveAble::Direction             _dire;
    LivingType                                  _type;
};

#endif //__MAGICITE_EFFECT_CREATE_FRIEND__