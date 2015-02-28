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
        const cocos2d::Vec2& pos,
        MagiciteGamePhyLayer* phyLayer,
        MagiciteGameMoveAble::Direction dire);

    virtual bool init(
        const cocos2d::Vec2& pos,
        MagiciteGamePhyLayer* phyLayer,
        MagiciteGameMoveAble::Direction dire);
};

#endif //__MAGICITE_SKILL_CARD_FIREBALL_