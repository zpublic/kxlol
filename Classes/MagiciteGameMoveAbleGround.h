#ifndef __MAGICITE_GAME_MOVEABLE_GROUND__
#define __MAGICITE_GAME_MOVEABLE_GROUND__

#include "MagiciteGameGround.h"
#include "MagiciteGameAutoMoveAble.h"

class MagiciteGameMoveAbleGround : public MagiciteGameGround, public MagiciteGameAutoMoveAble
{
public:

    enum : int { ground_speed = 3 };

    MagiciteGameMoveAbleGround();
    ~MagiciteGameMoveAbleGround();

    //MagiciteGameMoveAble

    virtual bool init();
    virtual bool initWithFile(const char* filename);

    CREATE_FUNC(MagiciteGameMoveAbleGround);

protected:
    //MagiciteGameAutoMoveAble

    virtual cocos2d::Vec2 getPos();

    void setBodyXSpeed(float x_speed);
    void setBodyYSpeed(float y_speed);
};

#endif //__MAGICITE_GAME_MOVEABLE_GROUND__
