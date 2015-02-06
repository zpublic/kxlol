#ifndef __MAGICITE_GAME_MOVEABLE_LIVING__
#define __MAGICITE_GAME_MOVEABLE_LIVING__

#include "cocos2d.h"
#include "MagiciteGameLiving.h"
#include "MagiciteGameMoveAble.h"

class MagiciteGameMoveAbleLiving : public MagiciteGameLiving, public MagiciteGameMoveAble
{
public:
    enum MoveLivingType : int
    {
        Unknow,
        Human_Type,
        Chicken_Type,
    }MoveAbleLivingType;

    MagiciteGameMoveAbleLiving(MoveLivingType type = Unknow);

    virtual void Move(Direction dire);
    virtual void Stop();
    virtual void Jump();
    virtual void JumpOver();

    virtual void initAnimation() = 0;
    virtual void startAnimation(AnimationTag);
    virtual void stopAnimation(AnimationTag);

    virtual bool init();
    virtual bool initWithFile(const char* filename);

protected:
    virtual cocos2d::RepeatForever* createAnimateJump() = 0;
    virtual cocos2d::RepeatForever* createAnimateMove() = 0;

    void setBodyXSpeed(float x_speed);
    void setBodyYSpeed(float y_speed);
};

#endif //__MAGICITE_GAME_MOVEABLE_LIVING__
