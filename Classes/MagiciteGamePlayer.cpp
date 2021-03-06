#include "MagiciteGamePlayer.h"
#include "MagiciteGameBagView.h"
#include "MagiciteEffectItem.h"
#include "MagiciteGamePet.h"
#include "MagiciteGameContact.h"
#include "MagiciteGamePhysics.h"
#include "MagiciteGameMoveAbleLiving.h"

USING_NS_CC;

MagiciteGamePlayer::MagiciteGamePlayer()
:_player(nullptr), _move_left(false), _move_right(false), _move_down(false)
{

}

MagiciteGamePlayer::~MagiciteGamePlayer()
{
    CC_SAFE_DELETE(_bag);
}

void MagiciteGamePlayer::Move()
{
    CCASSERT(_player != nullptr, "player is null");
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
    CCASSERT(_player != nullptr, "player is null");
    _player->Stop();
}

void MagiciteGamePlayer::Jump()
{
    CCASSERT(_player != nullptr, "player is null");
    if (_move_down)
    {
        //do something
        Through();
    }
    else
    {
        _player->Jump();
    }
}
void MagiciteGamePlayer::JumpOver()
{
    CCASSERT(_player != nullptr, "player is null");
    _player->JumpOver();
}

void MagiciteGamePlayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    switch (keyCode)
    {
    case EventKeyboard::KeyCode::KEY_UP_ARROW:
    case EventKeyboard::KeyCode::KEY_SPACE:
        this->Jump();
        break;
    case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        _move_down = true;
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
    case EventKeyboard::KeyCode::KEY_UP_ARROW:
    case EventKeyboard::KeyCode::KEY_SPACE:
        ThroughOver();
        break;
    case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        _move_down = false;
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        _move_left = false;
        this->Stop();
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        _move_right = false;
        this->Stop();
        break;
    default:
        //MagiciteGameControlAble::dispatchKeyRelease(keyCode, event, static_cast<MagiciteGameControlAble*>(_bag));
        break;
    }
}

void MagiciteGamePlayer::setPetFollow(MagiciteGamePet* pet)
{
    CCASSERT(_player != nullptr, "player is null");
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

void MagiciteGamePlayer::Through()
{
    using namespace Magicite;
    MagiciteGameContact::judge_contact[FIXTURE_TYPE_PLAYER][FIXTURE_TYPE_PLATFORM] = MagiciteGameContact::Cancle;
    MagiciteGameContact::judge_contact[FIXTURE_TYPE_PLATFORM][FIXTURE_TYPE_PLAYER] = MagiciteGameContact::Cancle;
    _player->getBody()->SetAwake(true);
}

void MagiciteGamePlayer::ThroughOver()
{
    using namespace Magicite;
    if (MagiciteGameContact::judge_contact[FIXTURE_TYPE_PLAYER][FIXTURE_TYPE_PLATFORM] == MagiciteGameContact::Cancle)
    {
        MagiciteGameContact::judge_contact[FIXTURE_TYPE_PLAYER][FIXTURE_TYPE_PLATFORM] = MagiciteGameContact::Calcture;
        MagiciteGameContact::judge_contact[FIXTURE_TYPE_PLATFORM][FIXTURE_TYPE_PLAYER] = MagiciteGameContact::Calcture;
    }
}