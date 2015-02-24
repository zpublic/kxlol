#ifndef __MAGICITE_EFFECT__
#define __MAGICITE_EFFECT__

class MagiciteEffect
{
public:

    enum Type : int
    {
        T_Unkwon,
    }EffectType;

    virtual void positive()
    {

    }
    virtual void negative()
    {

    }
};

#endif //__MAGICITE_EFFECT__