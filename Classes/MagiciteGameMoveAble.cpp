#include "MagiciteGameMoveAble.h"

MagiciteGameMoveAble::MagiciteGameMoveAble()
{
    _state[S_Move] = false;
    _state[S_Jump] = false;
    _state[S_Animate] = false;
    _speed = DEFAULT_SPEED;
    _base_speed = DEFAULT_SPEED;
    _jumpHeight = DEFAULT_JUMP_HEIGHT;
    _max_jump_time = DEFAULT_JUMP_TIME;
    _jump_time = 0;
    _is_to_left = false;
    _is_dire_changed = false;
    _has_animate = false;
}

void MagiciteGameMoveAble::setJumpHeight(int offset)
{
    _jumpHeight = offset;
}

int MagiciteGameMoveAble::getJumpHeight() const
{
    return _jumpHeight;
}

void MagiciteGameMoveAble::setSpeed(float value)
{
    _speed = value;
}

float MagiciteGameMoveAble::getSpeed() const
{
    return _speed;
}

void MagiciteGameMoveAble::setState(State state, bool x)
{
    _state[state] = x;
}

bool MagiciteGameMoveAble::getState(State state) const
{
    return _state.find(state)->second;
}

void MagiciteGameMoveAble::tryToStopAnimate()
{
    if (getState(S_Jump) == false && getState(S_Move) == false)
    {
        setState(S_Animate, false);
    }
}

MagiciteGameMoveAble::Direction MagiciteGameMoveAble::getDire() const
{
    return _is_to_left ? Direction::left : Direction::right;
}

void MagiciteGameMoveAble::setDire(Direction dire)
{
    if ((dire == Direction::left ? true : false) != _is_to_left)
    {
        _is_dire_changed = true;
        _is_to_left = !_is_to_left;
    }
}

void MagiciteGameMoveAble::setBaseSpeed(float value)
{
    _base_speed = value;
    _speed = value;
}

float MagiciteGameMoveAble::getBaseSpeed() const
{
    return _base_speed;
}

void MagiciteGameMoveAble::Move(Direction dire)
{
    setBodyXSpeed(_speed * dire);
    if (_has_animate)
    {
        if (getState(State::S_Jump) == false)
        {
            this->startAnimation(AnimationTag::Move_Tag);
        }
    }
    if (getState(State::S_Move) == false)
        setState(State::S_Move, true);
}

void MagiciteGameMoveAble::Stop()
{
    if (getState(State::S_Move))
    {
        setState(State::S_Move, false);
        setBodyXSpeed(0);
        if (_has_animate)
            this->stopAnimation(AnimationTag::Move_Tag);
    }
}

void MagiciteGameMoveAble::Jump()
{
    if (_jump_time < _max_jump_time)
    {
        setBodyYSpeed(_jumpHeight);
        ++_jump_time;
        if (_has_animate)
        {
            if (getState(State::S_Move))
            {
                this->stopAnimation(AnimationTag::Move_Tag);
            }
            this->stopAnimation(AnimationTag::Jump_Tag);
            this->startAnimation(AnimationTag::Jump_Tag);
        }
        setState(State::S_Jump, true);
    }
}

void MagiciteGameMoveAble::JumpOver()
{
    if (getState(State::S_Jump))
    {
        if (_has_animate)
        {
            this->stopAnimation(AnimationTag::Jump_Tag);
            if (getState(State::S_Move))
            {
                this->startAnimation(MagiciteGameMoveAble::Move_Tag);
            }
        }
        setState(State::S_Jump, false);
        _jump_time = 0;
    }
}

void MagiciteGameMoveAble::initAnimation()
{
    _has_animate = true;
}

void MagiciteGameMoveAble::setBodyXSpeed(float x_speed)
{

}

void MagiciteGameMoveAble::setBodyYSpeed(float y_speed)
{

}

void MagiciteGameMoveAble::startAnimation(AnimationTag)
{

}

void MagiciteGameMoveAble::stopAnimation(AnimationTag)
{

}