#ifndef __MAGICITE_GAME_DIRT__
#define __MAGICITE_GAME_DIRT__

#include "cocos2d.h"
#include "MagiciteGameMoveAbleLiving.h"

class MagiciteGameDirt : public MagiciteGameMoveAbleLiving
{
public:
    MagiciteGameDirt();

    enum : int
    {
        dirt_hp = 1,
        dirt_mp = 1,
        dirt_speed = 2,
    };

    virtual void initAnimation();

    virtual bool init();

    CREATE_FUNC(MagiciteGameDirt);
protected:
    cocos2d::RepeatForever* createAnimateJump();
    cocos2d::RepeatForever* createAnimateMove();
};

#endif //__MAGICITE_GAME_DIRE__