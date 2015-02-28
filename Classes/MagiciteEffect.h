#ifndef __MAGICITE_EFFECT__
#define __MAGICITE_EFFECT__

class MagiciteGameObject;

class MagiciteEffect
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