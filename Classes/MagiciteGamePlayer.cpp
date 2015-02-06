#include "MagiciteGamePlayer.h"

USING_NS_CC;

MagiciteGamePlayer::MagiciteGamePlayer()
:_player(nullptr)
{

}

MagiciteGamePlayer* MagiciteGamePlayer::create(PlayerType type)
{
    auto ptr = new MagiciteGamePlayer();
    if (ptr && ptr->init(type))
    {
        return ptr;
    }
    else
    {
        return nullptr;
    }
}

MagiciteGameMoveAbleLiving* MagiciteGamePlayer::getSprite()
{
    return _player;
}

bool MagiciteGamePlayer::init(PlayerType type)
{
    switch (type)
    {
    case MagiciteGamePlayer::Chicken_Type:
        _player = MagiciteGameChicken::create();
            break;
    case MagiciteGamePlayer::Human_Type:
        _player = MagiciteGameHuman::create();
        break;
    default:
        break;
    }
    return (_player != nullptr);
}

void MagiciteGamePlayer::useSkill(int skillId)
{
    _player->useSkill(skillId);
}

void MagiciteGamePlayer::useSkillEx()
{
    _player->useSkillEx();
}

void MagiciteGamePlayer::Move(MagiciteGameMoveAbleLiving::Direction dire)
{
    _player->Move(dire);
}

void MagiciteGamePlayer::Stop()
{
    _player->Stop();
}

void MagiciteGamePlayer::Jump()
{
    _player->Jump();
}
void MagiciteGamePlayer::JumpOver()
{
    _player->JumpOver();
}

void MagiciteGamePlayer::startAnimation(MagiciteGameMoveAbleLiving::AnimationTag tag)
{
    _player->startAnimation(tag);
}

void MagiciteGamePlayer::stopAnimation(MagiciteGameMoveAbleLiving::AnimationTag tag)
{
    _player->startAnimation(tag);
}

void MagiciteGamePlayer::setJumpHeight(int offset)
{
    _player->setJumpHeight(offset);
}

int MagiciteGamePlayer::getJumpHeight() const
{
    return _player->getJumpHeight();
}

void MagiciteGamePlayer::setSpeed(int value)
{
    _player->setSpeed(value);
}

int MagiciteGamePlayer::getSpeed() const
{
    return _player->getSpeed();
}

void MagiciteGamePlayer::setState(MagiciteGameMoveAbleLiving::State state, bool x)
{
    _player->setState(state, x);
}

bool MagiciteGamePlayer::getState(MagiciteGameMoveAbleLiving::State state) const
{
    return _player->getState(state);
}

void MagiciteGamePlayer::setPosition(Vec2 pos)
{
    _player->setPosition(pos);
}

Vec2 MagiciteGamePlayer::getPosition() const
{
    return _player->getPosition();
}

Size MagiciteGamePlayer::getContentSize() const
{
    return _player->getContentSize();
}

void MagiciteGamePlayer::setContentSize(Size size)
{
    _player->setContentSize(size);
}