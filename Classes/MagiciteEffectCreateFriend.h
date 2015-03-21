#ifndef __MAGICITE_EFFECT_CREATE_FRIEND__
#define __MAGICITE_EFFECT_CREATE_FRIEND__

#include "cocos2d.h"
#include "MagiciteEffectCreate.h"
#include "MagiciteGameFactoryMethod.h"

class MagiciteGameObject;

class MagiciteEffectCreateFriend : public MagiciteEffectCreate
{
public:

    typedef MagiciteGameFactoryMethod::LivingType LivingType;

    MagiciteEffectCreateFriend();

    //MagiciteEffectCreate
    virtual void positive(MagiciteGameObject* obj);

    static MagiciteEffectCreateFriend* create(LivingType type);

    virtual bool init(
        LivingType type);

private:
    LivingType                                  _type;
};

#endif //__MAGICITE_EFFECT_CREATE_FRIEND__