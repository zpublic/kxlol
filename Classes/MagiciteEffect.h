#ifndef __MAGICITE_EFFECT__
#define __MAGICITE_EFFECT__

#include "cocos2d.h"

class MagiciteGameObject;

class MagiciteEffect : public cocos2d::Ref
{
public:

    enum Type : int
    {
        T_Unkwon,
    }EffectType;

    virtual void positive(MagiciteGameObject* obj)
    {

    }
    virtual void negative()
    {

    }
};

#endif //__MAGICITE_EFFECT__