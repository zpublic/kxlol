#ifndef __MAGICITE_FOREVER_SKILL_CARD__
#define __MAGICITE_FOREVER_SKILL_CARD__

#include "MagiciteForeverItem.h"

class MagiciteForeverSkillCard : public MagiciteForeverItem
{
public:

    static std::string name;

    MagiciteForeverSkillCard();

    virtual bool init();
    virtual bool initWithFile(const char* filename);
};

#endif //__MAGICITE_FOREVER_SKILL_CARD__