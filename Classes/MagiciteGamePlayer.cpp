#include "MagiciteGamePlayer.h"
#include "MagiciteGameBagView.h"
#include "MagiciteEffectItem.h"
#include "MagiciteGamePet.h"
#include "MagiciteGameMoveAbleLiving.h"

USING_NS_CC;

MagiciteGamePlayer::MagiciteGamePlayer()
:_player(nullptr), _move_left(false), _move_right(false)
{

}

MagiciteGamePlayer::~MagiciteGamePlayer()
{
    CC_SAFE_DELETE(_bag);
}

void MagiciteGamePlayer::Move()
{
    if (_move_left && !_move_right)
    {
        _player->Move(MagiciteGameMoveAbleLiving::Direction::left);
    }
    else if (!_move_left && _move_right)
    {
        _player->Move(MagiciteGameMoveAbleLiving::Direction::right);
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
    default:
        //MagiciteGameControlAble::dispatchKeyPress(keyCode, event, static_cast<MagiciteGameControlAble*>(_bag));
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
        MagiciteGameControlAble::dispatchKeyRelease(keyCode, event, static_cast<MagiciteGameControlAble*>(_bag));
        break;
    }
}

void MagiciteGamePlayer::setPetFollow(MagiciteGamePet* pet)
{
    _player->addChild(pet);
}

MagiciteGameBagView* MagiciteGamePlayer::getBag()
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

MagiciteGamePlayer* MagiciteGamePlayer::create(MagiciteGameMoveAbleLiving* living)
{
    auto player = new MagiciteGamePlayer();
    if (player && player->init(living))
    {
        return player;
    }
    else
    {
        CC_SAFE_DELETE(player);
        return nullptr;
    }
}

bool MagiciteGamePlayer::init(MagiciteGameMoveAbleLiving* living)
{
    if (living == nullptr)
    {
        return false;
    }

    _player = living;
    _player->_is_contraled = true;
    _bag = MagiciteGameBagView::create(9);
    _bag->_itemEvent = std::bind(&MagiciteGamePlayer::useBagItem, this, std::placeholders::_1);

    return true;
}