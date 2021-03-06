#ifndef __MAGICITE_SKILL_CARD_FIREBALL_
#define __MAGICITE_SKILL_CARD_FIREBALL_

#include "cocos2d.h"
#include "MagiciteForeverSkillCard.h"

class MagiciteGamePhyLayer;

class MagiciteSkillCardFireBall : public MagiciteForeverSkillCard
{
public:
    MagiciteSkillCardFireBall();
    ~MagiciteSkillCardFireBall();

    static MagiciteSkillCardFireBall* create(MagiciteGamePhyLayer* phyLayer);

    virtual bool init(MagiciteGamePhyLayer* phyLayer);

    virtual MagiciteItem* clone();
protected:
    MagiciteGamePhyLayer*               _phyLayer;
};

#endif //__MAGICITE_SKILL_CARD_FIREBALL_