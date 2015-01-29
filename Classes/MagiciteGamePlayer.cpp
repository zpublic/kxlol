#include "MagiciteGamePlayer.h"

USING_NS_CC;

MagiciteGamePlayer::MagiciteGamePlayer()
:_is_to_left(false), _jumpHeight(0)
{

}

MagiciteGamePlayer::~MagiciteGamePlayer()
{

}

void MagiciteGamePlayer::playerMove(int offset)
{
    if (offset > 0)
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
    setPlayerState(PlayerState::Move, true);
    _body->SetLinearVelocity(b2Vec2(offset, _body->GetLinearVelocity().y));
}

void MagiciteGamePlayer::playerStop()
{
    setPlayerState(PlayerState::Move, false);
    _body->SetLinearVelocity(b2Vec2(0, _body->GetLinearVelocity().y));
}

MagiciteGamePlayer* MagiciteGamePlayer::create(const char* filename)
{
    auto ptr = new MagiciteGamePlayer();
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

bool MagiciteGamePlayer::initWithFile(const char* filename)
{
    if (!MagiciteGamePhySprite::initWithFile(filename))
    {
        return false;
    }

    setJumpHeight(10);
    setPlayerState(PlayerState::Move, false);
    setPlayerState(PlayerState::Jump, false);

    return true;
}

void MagiciteGamePlayer::setJumpHeight(int offset)
{
    _jumpHeight = offset;
}

void MagiciteGamePlayer::playerJump()
{
    if (!getPlayerState(PlayerState::Jump))
    {
        _body->SetLinearVelocity(b2Vec2(_body->GetLinearVelocity().x, _jumpHeight));
        setPlayerState(PlayerState::Jump, true);
    }
}

void MagiciteGamePlayer::setPlayerState(PlayerState state, bool x)
{
    _state[state] = x;
}

bool MagiciteGamePlayer::getPlayerState(PlayerState state)
{
    return _state[state];
}
