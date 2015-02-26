#include "MagiciteGamePlayer.h"

USING_NS_CC;

MagiciteGamePlayer::MagiciteGamePlayer()
:_player(nullptr), _move_left(false), _move_right(false)
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

    if (_player == nullptr)
    {
        return false;
    }
    _player->_is_contraled = true;
    return true;
}

void MagiciteGamePlayer::useSkill(MagiciteEffect* effect)
{
    _player->useSkill(effect);
}

void MagiciteGamePlayer::Move()
{
    if (_move_left && !_move_right)
    {
        _player->Move(MagiciteGamePlayer::Direction::left);
    }
    else if (!_move_left && _move_right)
    {
        _player->Move(MagiciteGamePlayer::Direction::right);
    }
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

void MagiciteGamePlayer::setSpeed(float value)
{
    _player->setSpeed(value);
}

float MagiciteGamePlayer::getSpeed() const
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

MagiciteGameMoveAbleLiving::Direction MagiciteGamePlayer::getDire() const
{
    return _player->getDire();
}

void MagiciteGamePlayer::setDire(MagiciteGameMoveAbleLiving::Direction dire)
{
    _player->setDire(dire);
}

void MagiciteGamePlayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    switch (keyCode)
    {
    case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
    case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:
        _player->Jump();
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        _move_left = true;
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        _move_right = true;
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_1:
        useSkill(MagiciteEffectSpeedUp::create());
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_2:
        useSkill(MagiciteEffectJumpHigh::create());
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_3:
        useSkill(MagiciteEffectSprint::create());
        break;
    default:
        break;
    }

}

void MagiciteGamePlayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    switch (keyCode)
    {
    case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        _move_left = false;
        _player->Stop();
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        _move_right = false;
        _player->Stop();
        break;
    default:
        break;
    }
}

void MagiciteGamePlayer::setPetFollow(MagiciteGameObject* pet)
{
    _player->addChild(pet);
}