#include "MagiciteGamePlayer.h"
#include "MagiciteEffectSpeedUp.h"
#include "MagiciteEffectJumpHigh.h"
#include "MagiciteEffectSprint.h"
#include "MagiciteEffectFireBall.h"
#include "MagiciteEffectCreateFriend.h"
#include "MagiciteGaemFactoryMethod.h"
#include "MagiciteGameChicken.h"
#include "MagiciteGameHuman.h"
#include "MagiciteGameBagView.h"
#include "MagiciteEffectFlash.h"
#include "MagiciteEffectItem.h"

USING_NS_CC;

MagiciteGamePlayer::MagiciteGamePlayer()
:_player(nullptr), _move_left(false), _move_right(false)
{

}

MagiciteGamePlayer::~MagiciteGamePlayer()
{
    CC_SAFE_DELETE(_bag);
}

MagiciteGamePlayer* MagiciteGamePlayer::create(PlayerType type, MagiciteGamePhyLayer* phyLayer)
{
    auto ptr = new MagiciteGamePlayer();
    if (ptr && ptr->init(type, phyLayer))
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

bool MagiciteGamePlayer::init(PlayerType type, MagiciteGamePhyLayer* phyLayer)
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
    _phyLayer = phyLayer;
    _bag = MagiciteGameBagView::create(9);
    _bag->_itemEvent = std::bind(&MagiciteGamePlayer::useBagItem, this, std::placeholders::_1);

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
    case EventKeyboard::KeyCode::KEY_UP_ARROW:
    case EventKeyboard::KeyCode::KEY_SPACE:
        _player->Jump();
        break;
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        _move_left = true;
        break;
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        _move_right = true;
        break;
    case EventKeyboard::KeyCode::KEY_1:
        useSkill(MagiciteEffectSpeedUp::create());
        break;
    case EventKeyboard::KeyCode::KEY_2:
        useSkill(MagiciteEffectJumpHigh::create());
        break;
    case EventKeyboard::KeyCode::KEY_3:
        useSkill(MagiciteEffectSprint::create());
        break;
    case EventKeyboard::KeyCode::KEY_C:
        _player->useSkill(MagiciteEffectCreateFriend::create(_phyLayer, MagiciteEffectCreateFriend::LivingType::Slime));
        break;
    case EventKeyboard::KeyCode::KEY_F:
        _player->useSkill(MagiciteEffectFireBall::create(_phyLayer));
        break;
    case EventKeyboard::KeyCode::KEY_A:
        _player->useSkill(MagiciteEffectFlash::create(_phyLayer, 200));
    case EventKeyboard::KeyCode::KEY_TAB:
        switchBagInvisible();
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

MagiciteGameContainerView* MagiciteGamePlayer::getBag()
{
    return _bag;
}

void MagiciteGamePlayer::useItem(MagiciteEffectItem* item)
{
    item->positive(_player);
}

void MagiciteGamePlayer::useBagItem(int n)
{
    auto item = _bag->getItem(n);
    if (item != nullptr)
    {
        if (item->_itemType == MagiciteItem::EffectItem)
        {
            useItem(reinterpret_cast<MagiciteEffectItem*>(item));
        }
    }
}

void MagiciteGamePlayer::switchBagInvisible()
{
    _bag->setViewInvisible(!_bag->getViewInvisible());
}