#include "MagiciteGameLayer.h"

USING_NS_CC;

bool MagiciteGameLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    this->setKeyboardEnabled(true);
    this->schedule(schedule_selector(MagiciteGameLayer::update));
    _visibleSize = Director::getInstance()->getVisibleSize();
    _origin = Director::getInstance()->getVisibleOrigin();

    _background = MagiciteGameMap::create();
    this->addChild(_background, 0);

    _player = Sprite::create("CloseSelected.png");
    _player->setPosition(Vec2(_visibleSize.width / 2 + _origin.x, _visibleSize.height / 2 + _origin.y));
    _move_left = false;
    _move_right = false;
    this->addChild(_player,1);

    return true;
}

void MagiciteGameLayer::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    switch (keyCode)
    {
    case cocos2d::EventKeyboard::KeyCode::KEY_A:
        _move_left = true;
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_D:
        _move_right = true;
        break;
    default:
        break;
    }
}

void MagiciteGameLayer::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    switch (keyCode)
    {
    case cocos2d::EventKeyboard::KeyCode::KEY_A:
        _move_left = false;
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_D:
        _move_right = false;
        break;
    default:
        break;
    }
}

void MagiciteGameLayer::update(float timeDelta)
{
    if (_move_left && !_move_right)
    {
        if (_player->getPositionX() > _visibleSize.width / 2 - _origin.x)
        {
            _player->setPositionX(_player->getPositionX() - 3);
        }
        else
        {
            _background->MoveMap(-3);
        }
    }
    else if (!_move_left && _move_right)
    {
        if (_player->getPositionX() < _visibleSize.width / 2 + _origin.x)
        {
            _player->setPositionX(_player->getPositionX() + 3);
        }
        else
        {
            _background->MoveMap(3);
        }
    }
}