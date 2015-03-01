#ifndef __MAGICITE_GAME_MOVEABLE__
#define __MAGICITE_GAME_MOVEABLE__

#include <map>
#include "MagiciteGameTagManager.h"

class MagiciteGameMoveAble
{
public:
    MagiciteGameMoveAble();

    enum Direction : int
    {
        left = -1,
        right = 1,
    };
    Direction getDire() const;
    void setDire(Direction dire);

    enum :int{
        DEFAULT_SPEED = 3,
        DEFAULT_JUMP_HEIGHT = 10,
        DEFAULT_JUMP_TIME = 3,
    };

    virtual void Move(Direction dire) = 0;
    virtual void Stop() = 0;
    virtual void Jump() = 0;
    virtual void JumpOver() = 0;

    void setJumpHeight(int offset);
    int getJumpHeight() const;

    void setSpeed(float value);
    float getSpeed() const;
    void setBaseSpeed(float value);
    float getBaseSpeed() const;

    enum State : int
    {
        S_Move,
        S_Jump,
        S_Animate,
    };

    void setState(State state, bool x);
    bool getState(State state) const;

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
protected:
    std::map<State, bool>           _state;
    bool                            _is_dire_changed;
    bool                            _is_to_left;
    int                             _jumpHeight;
    float                           _speed;
    float                           _base_speed;
    int                             _jump_time;
    int                             _max_jump_time;
};

#endif //__MAGICITE_GAME_MOVEABLE__