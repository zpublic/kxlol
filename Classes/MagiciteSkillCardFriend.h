#ifndef __MAGICITE_SKILL_CARD_FRIEND__
#define __MAGICITE_SKILL_CARD_FRIEND__

#include "cocos2d.h"
#include "MagiciteForeverSkillCard.h"
#include "MagiciteGameFactoryMethod.h"

class MagiciteGamePhyLayer;

class MagiciteSkillCardFriend : public MagiciteForeverSkillCard
{
public:
    typedef MagiciteGameFactoryMethod::LivingType LivingType;

    MagiciteSkillCardFriend();
    ~MagiciteSkillCardFriend();

    static MagiciteSkillCardFriend* create(
        LivingType type,
        MagiciteGamePhyLayer* phyLayer);

    virtual bool init(
        LivingType type,
        MagiciteGamePhyLayer* phyLayer);

    virtual MagiciteItem* clone();

protected:
    LivingType                                  _type;
    MagiciteGamePhyLayer*                       _phyLayer;
};

#endif //__MAGICITE_SKILL_CARD_FRIEND__