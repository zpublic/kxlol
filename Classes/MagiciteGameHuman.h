#ifndef __MAGICITE_GAME_HUMAN__
#define __MAGICITE_GAME_HUMAN__

#include "cocos2d.h"
#include "MagiciteGameMoveAbleLiving.h"

class MagiciteGameHuman :public MagiciteGameMoveAbleLiving
{
public:
    MagiciteGameHuman();

    enum :int
    {
        human_hp = 10,
        human_mp = 10,
    };

    virtual void useSkill(int skillId);
    virtual void useSkillEx();

    virtual void initAnimation();

    virtual bool init();

    CREATE_FUNC(MagiciteGameHuman);
protected:
    cocos2d::RepeatForever* createAnimateJump();
    cocos2d::RepeatForever* createAnimateMove();
};

#endif //__MAGICITE_GAME_HUMAN__