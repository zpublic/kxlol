#ifndef __MAGICITE_GAME_SLIME__
#define __MAGICITE_GAME_SLIME__

#include "cocos2d.h"
#include "MagiciteGameMoveAbleLiving.h"

class MagiciteGameSlime : public MagiciteGameMoveAbleLiving
{
public:
    MagiciteGameSlime();

    enum : int
    {
        slime_hp = 1,
        slime_mp = 1,
    };

    virtual void useSkill(int skillId);
    virtual void useSkillEx();

    //MagiciteGameMoveAbleLiving
    virtual void initAnimation();

    virtual bool init();

    CREATE_FUNC(MagiciteGameSlime);
protected:
    //MagiciteGameMoveAbleLiving
    cocos2d::RepeatForever* createAnimateJump();
    cocos2d::RepeatForever* createAnimateMove();
};

#endif //__MAGICITE_GAME_SLIME__