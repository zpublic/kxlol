#ifndef __MAGICITE_TEMP_SKILL_CARD__
#define  __MAGICITE_TEMP_SKILL_CARD__

#include "cocos2d.h"
#include "MagiciteTempItem.h"

class MagiciteTempSkillCard : public MagiciteTempItem
{
public:
    enum : int
    {
        life = 1,
    };

    static std::string name;

    MagiciteTempSkillCard();

};

#endif //__MAGICITE_TEMP_SKILL_CARD__