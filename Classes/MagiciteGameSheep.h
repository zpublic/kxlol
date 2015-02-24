#ifndef __MAGICITE_GAME_SHEEP__
#define __MAGICITE_GAME_SHEEP__

#include "cocos2d.h"
#include "MagiciteGameMoveAbleLiving.h"

class MagiciteGameSheep : public MagiciteGameMoveAbleLiving
{
public:
    MagiciteGameSheep();

    enum : int
    {
        sheep_hp = 1,
        sheep_mp = 1,
    };

    //MagiciteGameMoveAbleLiving
    virtual void initAnimation();

    virtual bool init();

    CREATE_FUNC(MagiciteGameSheep);

protected:
    //MagiciteGameMoveAbleLiving
    cocos2d::RepeatForever* createAnimateJump();
    cocos2d::RepeatForever* createAnimateMove();
};

#endif //__MAGICITE_GAME_SHEEP__