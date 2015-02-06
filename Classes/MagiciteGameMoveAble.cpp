#include "MagiciteGameMoveAble.h"

MagiciteGameMoveAble::MagiciteGameMoveAble()
{
    _state[S_Move] = false;
    _state[S_Jump] = false;
    _state[S_Animate] = false;
    _speed = DEFAULT_SPEED;
    _jumpHeight = DEFAULT_JUMP_HEIGHT;
    _is_to_left = false;
}

void MagiciteGameMoveAble::setJumpHeight(int offset)
{
    _jumpHeight = offset;
}

int MagiciteGameMoveAble::getJumpHeight() const
{
    return _jumpHeight;
}

void MagiciteGameMoveAble::setSpeed(int value)
{
    _speed = value;
}

int MagiciteGameMoveAble::getSpeed() const
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
    _is_to_left = (dire == Direction::left ? true : false);
}