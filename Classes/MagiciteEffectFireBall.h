#ifndef __MAGICITE_EFFECT_FIREBALL__
#define __MAGICITE_EFFECT_FIREBALL__

#include "cocos2d.h"
#include "MagiciteEffectShoot.h"

class MagiciteEffectFireBall : public MagiciteEffectShoot
{
public:

    MagiciteEffectFireBall();
   
    //MagiciteEffectShoot
    virtual void positive(MagiciteGameObject* obj);

    CREATE_FUNC(MagiciteEffectFireBall);

    virtual bool init();

};

#endif //__MAGICITE_EFFECT_FIREBALL__