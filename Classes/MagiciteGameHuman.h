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
        human_hp = 1,
        human_mp = 1,
        human_speed = 4,
    };

    virtual void initAnimation();

    virtual bool init();

    CREATE_FUNC(MagiciteGameHuman);
protected:
    cocos2d::RepeatForever* createAnimateJump();
    cocos2d::RepeatForever* createAnimateMove();
};

#endif //__MAGICITE_GAME_HUMAN__