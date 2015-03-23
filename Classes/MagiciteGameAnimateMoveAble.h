#ifndef __MAGICITE_GAME_ANIMATE_MOVEABLE__
#define  __MAGICITE_GAME_ANIMATE_MOVEABLE__

#include "cocos2d.h"
#include "MagiciteGameMoveAble.h"

class MagiciteGameAnimateMoveAble : public MagiciteGameMoveAble
{
public:
    MagiciteGameAnimateMoveAble();
    ~MagiciteGameAnimateMoveAble();

    virtual void Move(Direction dire);
    virtual void Stop();
    virtual void Jump();
    virtual void JumpOver();

    enum AnimationTag : int
    {
        Move_Tag = MagiciteGameTagManager::Move_Tag,
        Jump_Tag = MagiciteGameTagManager::Jump_Tag,
    };

    virtual void initAnimation() = 0;
    virtual void startAnimation(AnimationTag) = 0;
    virtual void stopAnimation(AnimationTag) = 0;

protected:
    void tryToStopAnimate();
};

#endif //__MAGICITE_GAME_ANIMATE_MOVEABLE__