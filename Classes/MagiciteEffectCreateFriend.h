#ifndef __MAGICITE_EFFECT_CREATE_FRIEND__
#define __MAGICITE_EFFECT_CREATE_FRIEND__

#include "cocos2d.h"
#include "MagiciteEffectCreate.h"
#include "MagiciteGaemFactoryMethod.h"
#include "MagiciteGameMoveAble.h"

class MagiciteGameObject;
class MagiciteGamePhyLayer;

class MagiciteEffectCreateFriend : public MagiciteEffectCreate
{
public:

    typedef MagiciteGaemFactoryMethod::LivingType LivingType;

    MagiciteEffectCreateFriend();

    //MagiciteEffectCreate
    virtual void positive(MagiciteGameObject* obj);

    static MagiciteEffectCreateFriend* create(
        MagiciteGamePhyLayer* phyLayer,
        MagiciteGameMoveAble::Direction dire,
        LivingType type);

    virtual bool init(
        MagiciteGamePhyLayer* phyLayer,
        MagiciteGameMoveAble::Direction dire,
        LivingType type);

private:
    MagiciteGamePhyLayer*                       _phyLayer;
    MagiciteGameMoveAble::Direction             _dire;
    LivingType                                  _type;
};

#endif //__MAGICITE_EFFECT_CREATE_FRIEND__