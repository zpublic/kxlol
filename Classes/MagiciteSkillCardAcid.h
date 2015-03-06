#ifndef __MAGICITE_SKILL_CARD_ACID__
#define __MAGICITE_SKILL_CARD_ACID__

#include "cocos2d.h"
#include "MagiciteForeverSkillCard.h"

class MagiciteGamePhyLayer;

class MagiciteSkillCardAcid : public MagiciteForeverSkillCard
{
public:
    MagiciteSkillCardAcid();
    ~MagiciteSkillCardAcid();

    static MagiciteSkillCardAcid* create(MagiciteGamePhyLayer* phyLayer);

    virtual bool init(MagiciteGamePhyLayer* phyLayer);

    virtual MagiciteItem* clone();
protected:
    MagiciteGamePhyLayer*               _phyLayer;
};

#endif //__MAGICITE_SKILL_CARD_ACID__