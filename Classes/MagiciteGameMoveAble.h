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

    virtual void Move(Direction dire);
    virtual void Stop();
    virtual void Jump();
    virtual void JumpOver();

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
    virtual void initAnimation();
    virtual void startAnimation(AnimationTag);
    virtual void stopAnimation(AnimationTag);

protected:
    void tryToStopAnimate();

    virtual void setBodyXSpeed(float x_speed) = 0;
    virtual void setBodyYSpeed(float y_speed) = 0;

protected:
    std::map<State, bool>           _state;
    int                             _jumpHeight;
    int                             _jump_time;
    int                             _max_jump_time;
    float                           _speed;
    float                           _base_speed;
    bool                            _is_dire_changed;
    bool                            _is_to_left;
    bool                            _has_animate;
};

#endif //__MAGICITE_GAME_MOVEABLE__