#ifndef __MAGICITE_GAME_CHICKEN__
#define __MAGICITE_GAME_CHICKEN__

#include "cocos2d.h"
#include "MagiciteGameMoveAbleLiving.h"

class MagiciteGameChicken : public MagiciteGameMoveAbleLiving
{
public:
    MagiciteGameChicken();

    virtual void useSkill(int skillId);
    virtual void useSkillEx();

    virtual void initAnimation();

    virtual bool init();

    CREATE_FUNC(MagiciteGameChicken);
protected:
    cocos2d::RepeatForever* createAnimateJump();
    cocos2d::RepeatForever* createAnimateMove();
};

#endif //__MAGICITE_GAME_CHICKEN__