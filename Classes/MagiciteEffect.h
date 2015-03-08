#ifndef __MAGICITE_EFFECT__
#define __MAGICITE_EFFECT__

#include "cocos2d.h"

class MagiciteGameObject;

class MagiciteEffect : public cocos2d::Ref
{
public:

    MagiciteEffect() :_coolDown(0){};

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

    long long getCD() const
    {
        return _coolDown;
    }

protected:
    void setCd(long long cd)
    {
        _coolDown = cd;
    }

    long long                           _coolDown;
};

#endif //__MAGICITE_EFFECT__