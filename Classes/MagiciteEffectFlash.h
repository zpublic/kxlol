#ifndef __MAGICITE_EFFECT_FLASH__
#define __MAGICITE_EFFECT_FLASH__

#include "cocos2d.h"
#include "MagiciteEffectPositive.h"
#include "MagiciteGamePhyLayer.h"
#include "MagiciteGameMoveAbleLiving.h"

class MagiciteEffectFlash : public MagiciteEffectPositive
{
public:
    MagiciteEffectFlash(MagiciteGamePhyLayer* phyLayer, MagiciteGameMoveAbleLiving* player, float length);

    //MagiciteEffectPositive
    virtual void positive();
    virtual void negative();

private:
    MagiciteGamePhyLayer*                               _phyLayer;
    MagiciteGameMoveAbleLiving*                         _player;
    float                                               _length;
};

#endif //__MAGICITE_EFFECT_FLASH__