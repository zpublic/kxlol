#include "MagiciteGameMoveAbleLiving.h"

USING_NS_CC;

MagiciteGameMoveAbleLiving::MagiciteGameMoveAbleLiving(MoveLivingType type /*= Unknow*/)
:MagiciteGameLiving(MoveAbleType::MoveAbleLiving), MoveAbleLivingType(type), _is_contraled(false), _is_friend(false)
{

}

MagiciteGameMoveAbleLiving::~MagiciteGameMoveAbleLiving()
{
    _jumpAnimate->release();
    _moveAnimate->release();
}

bool MagiciteGameMoveAbleLiving::init()
{
    if (!MagiciteGameLiving::init())
    {
        return false;
    }
    this->initAnimation();
    return true;
}

bool MagiciteGameMoveAbleLiving::initWithFile(const char* filename)
{
    if (!MagiciteGameLiving::initWithFile(filename))
    {
        return false;
    }
    this->initAnimation();
    createAnimate();

    return true;
}

void MagiciteGameMoveAbleLiving::Move(Direction dire)
{
    if (_is_dire_changed)
    {
        this->setFlippedX(_is_to_left);
        _is_dire_changed = false;
    }
    else if (dire == Direction::right)
    {
        if (_is_to_left)
        {
            _is_to_left = !_is_to_left;
            this->setFlippedX(_is_to_left);
        }
    }
    else
    {
        if (!_is_to_left)
        {
            _is_to_left = !_is_to_left;
            this->setFlippedX(_is_to_left);
        }
    }
    setBodyXSpeed(_speed * dire);
    if (getState(State::S_Jump) == false)
    {
        this->startAnimation(AnimationTag::Move_Tag);
    }
    if (getState(State::S_Move) == false)
    setState(State::S_Move, true);
}

void MagiciteGameMoveAbleLiving::Stop()
{
    if (getState(State::S_Move))
    {
        setState(State::S_Move, false);
        setBodyXSpeed(0);
        this->stopAnimation(AnimationTag::Move_Tag);
    }
}

void MagiciteGameMoveAbleLiving::Jump()
{
    if (_jump_time < _max_jump_time)
    {
        setBodyYSpeed(_jumpHeight);
        ++_jump_time;
        if (getState(State::S_Move))
        {
            this->stopAnimation(AnimationTag::Move_Tag);
        }
        this->stopAnimation(AnimationTag::Jump_Tag);
        this->startAnimation(AnimationTag::Jump_Tag);
        setState(State::S_Jump, true);
    }
}

void MagiciteGameMoveAbleLiving::JumpOver()
{
    if (getState(State::S_Jump))
    {
        this->stopAnimation(AnimationTag::Jump_Tag);
        if (getState(State::S_Move))
        {
            this->startAnimation(MagiciteGameMoveAble::Move_Tag);
        }
        setState(State::S_Jump, false);
        _jump_time = 0;
    }
}

void MagiciteGameMoveAbleLiving::setBodyXSpeed(float x_speed)
{
    getBody()->SetLinearVelocity(b2Vec2(x_speed, getBody()->GetLinearVelocity().y));
}

void MagiciteGameMoveAbleLiving::setBodyYSpeed(float y_speed)
{
    getBody()->SetLinearVelocity(b2Vec2(getBody()->GetLinearVelocity().x, y_speed));
}

void MagiciteGameMoveAbleLiving::startAnimation(AnimationTag tag)
{
    switch (tag)
    {
    case MagiciteGameMoveAble::Move_Tag:
        if (getState(State::S_Move) == false || getState(State::S_Jump))
        {
            this->runAction(getMoveAnimate());
        }
        break;
    case MagiciteGameMoveAble::Jump_Tag:
        if (getState(State::S_Jump) == false)
        {
            this->runAction(getJumpAnimate());
        }
        break;
    default:
        break;
    }
    setState(State::S_Animate, true);
}

void MagiciteGameMoveAbleLiving::stopAnimation(AnimationTag tag)
{
    if (getState(State::S_Animate))
    {
        this->stopAllActionsByTag(tag);
        tryToStopAnimate();
    }
}

RepeatForever* MagiciteGameMoveAbleLiving::getJumpAnimate()
{
    return _jumpAnimate;
}

RepeatForever* MagiciteGameMoveAbleLiving::getMoveAnimate()
{
    return _moveAnimate;
}

void MagiciteGameMoveAbleLiving::createAnimate()
{
    _jumpAnimate = this->createAnimateJump();
    _jumpAnimate->retain();
    _moveAnimate = this->createAnimateMove();
    _moveAnimate->retain();
}