#ifndef __MAGICITE_EFFECT__
#define __MAGICITE_EFFECT__

#include "cocos2d.h"

class MagiciteGameObject;

class MagiciteEffect : public cocos2d::Ref
{
public:

    MagiciteEffect() :_coolDown(0){}

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

    int getCD() const
    {
        return this->_coolDown;
    }

protected:
    void setCd(int cd)
    {
        _coolDown = cd;
    }

    int                              _coolDown;
};

#endif //__MAGICITE_EFFECT__