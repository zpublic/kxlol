#ifndef __MAGICITE_GAME_MOVE_PITFALL__
#define __MAGICITE_GAME_MOVE_PITFALL__

#include "MagiciteGamePitfall.h"
#include "MagiciteGameMoveAble.h"

class MagiciteGameMovePitfall : public MagiciteGamePitfall, public MagiciteGameMoveAble
{
public:
    MagiciteGameMovePitfall();
    ~MagiciteGameMovePitfall();

    virtual bool init();
    virtual bool initWithFile(const char* filename);

    //MagiciteGameMoveAble
    virtual void Move(Direction dire);
    virtual void Stop();
    virtual void Jump();
    virtual void JumpOver();

    virtual void initAnimation();
    virtual void startAnimation(AnimationTag);
    virtual void stopAnimation(AnimationTag);

protected:
    void setBodyXSpeed(float x_speed);
    void setBodyYSpeed(float y_speed);

};

#endif //__MAGICITE_GAME_MOVE_PITFALL__