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

    MagiciteEffectCreateFriend();

    //MagiciteEffectCreate
    virtual void positive();

    static MagiciteEffectCreateFriend* create(
        const cocos2d::Vec2& pos,
        MagiciteGamePhyLayer* phyLayer,
        MagiciteGameMoveAble::Direction dire,
        LivingType type);

    virtual bool init(
        const cocos2d::Vec2& pos,
        MagiciteGamePhyLayer* phyLayer,
        MagiciteGameMoveAble::Direction dire,
        LivingType type);

private:
    cocos2d::Vec2                               _pos;
    MagiciteGamePhyLayer*                       _phyLayer;
    MagiciteGameMoveAble::Direction             _dire;
    LivingType                                  _type;
};

#endif //__MAGICITE_EFFECT_CREATE_FRIEND__