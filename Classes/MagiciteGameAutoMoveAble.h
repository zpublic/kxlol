#ifndef __MAGICITE_GAME_AUTO_MOVEABLE__
#define __MAGICITE_GAME_AUTO_MOVEABLE__

#include "MagiciteGameMoveAble.h"
#include "cocos2d.h"

class MagiciteGameAutoMoveAble : public MagiciteGameMoveAble
{
public:
    cocos2d::Vec2               _pointA;
    cocos2d::Vec2               _pointB;

    virtual void AutoMove();

protected:
    virtual cocos2d::Vec2 getPos() = 0;
};

#endif //__MAGICITE_GAME_AUTO_MOVEABLE__
