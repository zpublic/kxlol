#ifndef __MAGICITE_SKILL_CARD_FIREBALL_
#define __MAGICITE_SKILL_CARD_FIREBALL_

#include "cocos2d.h"
#include "MagiciteForeverSkillCard.h"
#include "MagiciteGameMoveAble.h"

class MagiciteGamePhyLayer;

class MagiciteSkillCardFireBall : public MagiciteForeverSkillCard
{
public:
    MagiciteSkillCardFireBall();
    ~MagiciteSkillCardFireBall();

    static MagiciteSkillCardFireBall* create(
        MagiciteGamePhyLayer* phyLayer,
        MagiciteGameMoveAble::Direction dire);

    virtual bool init(
        MagiciteGamePhyLayer* phyLayer,
        MagiciteGameMoveAble::Direction dire);

    virtual MagiciteGameObject* getItemObject();
};

#endif //__MAGICITE_SKILL_CARD_FIREBALL_