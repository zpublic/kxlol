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
            setFlipX(_is_to_left);
        }
    }
    else
    {
        if (!_is_to_left)
        {
            _is_to_left = !_is_to_left;
            setFlipX(_is_to_left);
        }
    }
    _body->SetLinearVelocity(b2Vec2(offset, _body->GetLinearVelocity().y));
}

void MagiciteGamePlayer::playerStop()
{
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
    return true;
}

void MagiciteGamePlayer::setJumpHeight(int offset)
{
    _jumpHeight = offset;
}

void MagiciteGamePlayer::playerJump()
{
    if (fabs(_body->GetLinearVelocity().y) <= JUMP_EPSINON)
    {
        _body->SetLinearVelocity(b2Vec2(_body->GetLinearVelocity().x, _jumpHeight));
    }
}