#include "MagiciteGameLivine.h"

USING_NS_CC;

MagiciteGameLivine::MagiciteGameLivine()
:_is_to_left(false), _jumpHeight(0), _speed(0)
{

}

MagiciteGameLivine::~MagiciteGameLivine()
{

}

void MagiciteGameLivine::Move(Direction dire)
{
    if (dire == Direction::right)
    {
        if (_is_to_left)
        {
            _is_to_left = !_is_to_left;
            setFlippedX(_is_to_left);
        }
    }
    else
    {
        if (!_is_to_left)
        {
            _is_to_left = !_is_to_left;
            setFlippedX(_is_to_left);
        }
    }
    setState(State::S_Move, true);
    _body->SetLinearVelocity(b2Vec2(_speed * dire, _body->GetLinearVelocity().y));
}

void MagiciteGameLivine::Stop()
{
    setState(State::S_Move, false);
    _body->SetLinearVelocity(b2Vec2(0, _body->GetLinearVelocity().y));
}

MagiciteGameLivine* MagiciteGameLivine::create(const char* filename)
{
    auto ptr = new MagiciteGameLivine();
    if (ptr && ptr->initWithFile(filename))
    {
        ptr->autorelease();
        return ptr;
    }
    else
    {
        CC_SAFE_DELETE(ptr);
        return nullptr;
    }
}

bool MagiciteGameLivine::initWithFile(const char* filename)
{
    if (!MagiciteGamePhySprite::initWithFile(filename))
    {
        return false;
    }

    setJumpHeight(DEFAULT_JUMP_HEIGHT);
    setSpeed(DEFAULT_SPEED);
    setState(State::S_Move, false);
    setState(State::S_Jump, false);

    return true;
}

void MagiciteGameLivine::setJumpHeight(int offset)
{
    _jumpHeight = offset;
}

void MagiciteGameLivine::Jump()
{
    if (!getState(State::S_Jump))
    {
        _body->SetLinearVelocity(b2Vec2(_body->GetLinearVelocity().x, _jumpHeight));
        setState(State::S_Jump, true);
    }
}

void MagiciteGameLivine::setState(State state, bool x)
{
    _state[state] = x;
}

bool MagiciteGameLivine::getState(State state)
{
    return _state[state];
}

void MagiciteGameLivine::setSpeed(int value)
{
    _speed = value;
}

void MagiciteGameLivine::useSkill(int skillId)
{

}

void MagiciteGameLivine::useSkillEx()
{

}