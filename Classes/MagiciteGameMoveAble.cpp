#include "MagiciteGameMoveAble.h"

MagiciteGameMoveAble::MagiciteGameMoveAble()
{
    _state[S_Move] = false;
    _state[S_Jump] = false;
    _state[S_Animate] = false;
    _speed = DEFAULT_SPEED;
    _base_speed = DEFAULT_SPEED;
    _jumpHeight = DEFAULT_JUMP_HEIGHT;
    _is_to_left = false;
    _is_dire_changed = false;
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