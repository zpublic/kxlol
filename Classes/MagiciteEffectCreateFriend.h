#ifndef __MAGICITE_EFFECT_CREATE_FRIEND__
#define __MAGICITE_EFFECT_CREATE_FRIEND__

#include "cocos2d.h"
#include "MagiciteEffectCreate.h"
#include "MagiciteGameFactoryMethod.h"

class MagiciteGameObject;
class MagiciteGamePhyLayer;

class MagiciteEffectCreateFriend : public MagiciteEffectCreate
{
public:

    enum : long long { cool_down = 3 };

    typedef MagiciteGameFactoryMethod::LivingType LivingType;

    MagiciteEffectCreateFriend();

    //MagiciteEffectCreate
    virtual void positive(MagiciteGameObject* obj);

    static MagiciteEffectCreateFriend* create(
        MagiciteGamePhyLayer* phyLayer,
        LivingType type);

    virtual bool init(
        MagiciteGamePhyLayer* phyLayer,
        LivingType type);

private:
    MagiciteGamePhyLayer*                       _phyLayer;
    LivingType                                  _type;
};

#endif //__MAGICITE_EFFECT_CREATE_FRIEND__