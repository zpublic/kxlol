#ifndef __MAGICITE_GAME_CHICKEN__
#define __MAGICITE_GAME_CHICKEN__

#include "cocos2d.h"
#include "MagiciteGameMoveAbleLiving.h"

class MagiciteGameChicken : public MagiciteGameMoveAbleLiving
{
public:
    MagiciteGameChicken();

    enum : int
    {
        chicken_hp = 1,
        chicken_mp = 1,
        chicken_speed = 3,
    };

    virtual void initAnimation();

    virtual bool init();

    CREATE_FUNC(MagiciteGameChicken);
protected:
    cocos2d::RepeatForever* createAnimateJump();
    cocos2d::RepeatForever* createAnimateMove();
};

#endif //__MAGICITE_GAME_CHICKEN__