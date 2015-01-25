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
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

	_background = MagiciteGameMap::create();

	_player = Sprite::create("CloseSelected.png");
	_player->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	_is_move = false;
	_left_or_right = _direction::right;

    /*auto act = MoveTo::create(1.0f, Vec2(250, 200));
    sprite->runAction(act);*/


	this->addChild(_background, 0);
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
		cocos2d::log("D");
		_is_move = false;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_A:
		cocos2d::log("A");

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
			if (_player->getPositionX() < visibleSize.width / 2 + origin.x)
			{
				_player->setPositionX(_player->getPositionX() + seed);
			}
			else
			{
				_background->MoveMap(seed);
			}
		}
		else
		{
			if (_player->getPositionX() > origin.x)
				_player->setPositionX(_player->getPositionX() - seed);
		}
	}
}