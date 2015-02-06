#ifndef __MAGICITE_GAME_LIVING__
#define __MAGICITE_GAME_LIVING__

#include "cocos2d.h"
#include "MagiciteGameObject.h"

class MagiciteGameLiving : public MagiciteGameObject
{
public:
    enum MoveAbleType : int
    {
        MoveAbleLiving,
        NormalLiving,
    }LivingMoveType;

    enum LivingType : int
    {
        Unknow,
        Piranha,
    }NormalLivingType;

    MagiciteGameLiving(
        MoveAbleType movetype = MoveAbleType::NormalLiving, 
        LivingType livingtype = LivingType::Unknow);

    virtual void useSkill(int skillId) = 0;
    virtual void useSkillEx() = 0;

    virtual bool init();
    virtual bool initWithFile(const char* filename);
};

#endif //__MAGICITE_GAME_LIVING__