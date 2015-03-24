#include "MagiciteGameAnimateMoveAble.h"

USING_NS_CC;

MagiciteGameAnimateMoveAble::MagiciteGameAnimateMoveAble()
{

}

MagiciteGameAnimateMoveAble::~MagiciteGameAnimateMoveAble()
{

}

void MagiciteGameAnimateMoveAble::Move(Direction dire)
{
    if (getState(State::S_Jump) == false)
    {
        this->startAnimation(AnimationTag::Move_Tag);
    }
    MagiciteGameMoveAble::Move(dire);
}

void MagiciteGameAnimateMoveAble::Stop()
{
    if (getState(State::S_Move))
    {
        MagiciteGameMoveAble::Stop();
        this->stopAnimation(AnimationTag::Move_Tag);
    }
}

void MagiciteGameAnimateMoveAble::Jump()
{
    if (_jump_time < _max_jump_time)
    {
        if (getState(State::S_Move))
        {
            this->stopAnimation(AnimationTag::Move_Tag);
        }
        this->stopAnimation(AnimationTag::Jump_Tag);
        this->startAnimation(AnimationTag::Jump_Tag);
        MagiciteGameMoveAble::Jump();
    }
}

void MagiciteGameAnimateMoveAble::JumpOver()
{
    if (getState(State::S_Jump))
    {
        this->stopAnimation(AnimationTag::Jump_Tag);
        if (getState(State::S_Move))
        {
            this->startAnimation(AnimationTag::Move_Tag);
        }
        MagiciteGameMoveAble::JumpOver();
    }
}

void MagiciteGameAnimateMoveAble::tryToStopAnimate()
{
    if (getState(S_Jump) == false && getState(S_Move) == false)
    {
        setState(S_Animate, false);
    }
}