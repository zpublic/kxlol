#ifndef __MAGICITE_SKILL_CARD_FRIEND__
#define __MAGICITE_SKILL_CARD_FRIEND__

#include "cocos2d.h"
#include "MagiciteForeverSkillCard.h"
#include "MagiciteGameMoveAble.h"
#include "MagiciteGaemFactoryMethod.h"

class MagiciteGamePhyLayer;

class MagiciteSkillCardFriend : public MagiciteForeverSkillCard
{
public:
    typedef MagiciteGaemFactoryMethod::LivingType LivingType;

    MagiciteSkillCardFriend();
    ~MagiciteSkillCardFriend();

    static MagiciteSkillCardFriend* create(
        LivingType type,
        MagiciteGamePhyLayer* phyLayer,
        MagiciteGameMoveAble::Direction dire);

    virtual bool init(
        LivingType type,
        MagiciteGamePhyLayer* phyLayer,
        MagiciteGameMoveAble::Direction dire);
};

#endif //__MAGICITE_SKILL_CARD_FRIEND__