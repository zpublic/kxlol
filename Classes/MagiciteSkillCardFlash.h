#ifndef __MAGICITE_SKILL_CARD_FLASH__
#define __MAGICITE_SKILL_CARD_FLASH__

#include "MagiciteForeverSkillCard.h"

class MagiciteGamePhyLayer;

class MagiciteSkillCardFlash : public MagiciteForeverSkillCard
{
public:
    MagiciteSkillCardFlash();
    ~MagiciteSkillCardFlash();

    static MagiciteSkillCardFlash* create(MagiciteGamePhyLayer* phyLayer, float length);

    virtual bool init(MagiciteGamePhyLayer* phyLayer, float length);

    MagiciteItem* clone();

protected:
    MagiciteGamePhyLayer*                       _phyLayer;
    float                                       _length;
};

#endif //__MAGICITE_SKILL_CARD_FLASH__