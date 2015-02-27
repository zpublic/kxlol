#ifndef __MAGICITE_EFFECT_FLASH__
#define __MAGICITE_EFFECT_FLASH__

#include "cocos2d.h"
#include "MagiciteEffectPositive.h"

class MagiciteGamePhyLayer;
class MagiciteGameMoveAbleLiving;

class MagiciteEffectFlash : public MagiciteEffectPositive
{
public:
    MagiciteEffectFlash();

    //MagiciteEffectPositive
    virtual void positive(MagiciteGameObject* obj);
    virtual void negative();

    static MagiciteEffectFlash* create(MagiciteGamePhyLayer* phyLayer, float length);

    virtual bool init(MagiciteGamePhyLayer* phyLayer, float length);

private:
    MagiciteGamePhyLayer*                               _phyLayer;
    float                                               _length;
};

#endif //__MAGICITE_EFFECT_FLASH__