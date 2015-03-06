#ifndef __MAGICITE_SKILL_CARD_SPRINT__
#define __MAGICITE_SKILL_CARD_SPRINT__

#include "MagiciteForeverSkillCard.h"

class MagiciteSkillCardSprint : public MagiciteForeverSkillCard
{
public:
    MagiciteSkillCardSprint();
    ~MagiciteSkillCardSprint();

    virtual bool init();
    CREATE_FUNC(MagiciteSkillCardSprint);

    MagiciteItem* clone();
};

#endif //__MAGICITE_SKILL_CARD_SPRINT__