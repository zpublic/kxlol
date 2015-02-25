#ifndef __MAGICITE_EFFECT_FLASH__
#define __MAGICITE_EFFECT_FLASH__

#include "cocos2d.h"
#include "MagiciteEffectPositive.h"
#include "MagiciteGamePhyLayer.h"
#include "MagiciteGameMoveAbleLiving.h"

class MagiciteEffectFlash : public MagiciteEffectPositive
{
public:
    MagiciteEffectFlash();

    //MagiciteEffectPositive
    virtual void positive();
    virtual void negative();

    static MagiciteEffectFlash* create(MagiciteGamePhyLayer* phyLayer, MagiciteGameMoveAbleLiving* player, float length);

    virtual bool init(MagiciteGamePhyLayer* phyLayer, MagiciteGameMoveAbleLiving* player, float length);

private:
    MagiciteGamePhyLayer*                               _phyLayer;
    MagiciteGameMoveAbleLiving*                         _player;
    float                                               _length;
};

#endif //__MAGICITE_EFFECT_FLASH__