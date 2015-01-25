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
    _is_move = false;
    _left_or_right = _direction::right;
    this->addChild(_player,1);

    return true;
}

void MagiciteGameLayer::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    switch (keyCode)
    {
    case cocos2d::EventKeyboard::KeyCode::KEY_D:
        _left_or_right = _direction::right;
        _is_move = true;
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_A:
        _left_or_right = _direction::left;
        _is_move = true;
        break;
    default:
        break;
    }
}
void MagiciteGameLayer::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    switch (keyCode)
    {
    case cocos2d::EventKeyboard::KeyCode::KEY_D:
        _is_move = false;
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_A:
        _is_move = false;
        break;
    default:
        break;
    }
    _is_move = false;
}

void MagiciteGameLayer::update(float timeDelta)
{
    if (_is_move)
    {
        if (_left_or_right == _direction::right)
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
        else
        {
            if (_player->getPositionX() > _origin.x)
                _player->setPositionX(_player->getPositionX() - 3);
        }
    }
}