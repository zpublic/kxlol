#ifndef __MAGICITE_SKILL_CARD_SPEED_UP__
#define __MAGICITE_SKILL_CARD_SPEED_UP__

#include "MagiciteForeverSkillCard.h"

class MagiciteSkillCardSpeedUp : public MagiciteForeverSkillCard
{
public:
    MagiciteSkillCardSpeedUp();
    ~MagiciteSkillCardSpeedUp();

    virtual bool init();

    CREATE_FUNC(MagiciteSkillCardSpeedUp);

    MagiciteItem* clone();
};

#endif //__MAGICITE_SKILL_CARD_SPEED_UP__