#include "MagiciteGameLiving.h"

USING_NS_CC;

MagiciteGameLiving::MagiciteGameLiving()
:_is_to_left(false), _jumpHeight(0), _speed(0), _LivingType(LivingType::T_Unknow)
{
    _SpriteType = MagiciteGamePhySprite::SpriteType::T_Living;
}

MagiciteGameLiving::~MagiciteGameLiving()
{

}

void MagiciteGameLiving::Move(Direction dire)
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

void MagiciteGameLiving::Stop()
{
    setState(State::S_Move, false);
    _body->SetLinearVelocity(b2Vec2(0, _body->GetLinearVelocity().y));
}

MagiciteGameLiving* MagiciteGameLiving::create(const char* filename)
{
    auto ptr = new MagiciteGameLiving();
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

bool MagiciteGameLiving::initWithFile(const char* filename)
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

void MagiciteGameLiving::setJumpHeight(int offset)
{
    _jumpHeight = offset;
}

void MagiciteGameLiving::Jump()
{
    if (!getState(State::S_Jump))
    {
        _body->SetLinearVelocity(b2Vec2(_body->GetLinearVelocity().x, _jumpHeight));
        setState(State::S_Jump, true);
    }
}

void MagiciteGameLiving::setState(State state, bool x)
{
    _state[state] = x;
}

bool MagiciteGameLiving::getState(State state)
{
    return _state[state];
}

void MagiciteGameLiving::setSpeed(int value)
{
    _speed = value;
}

void MagiciteGameLiving::useSkill(int skillId)
{

}

void MagiciteGameLiving::useSkillEx()
{

}
