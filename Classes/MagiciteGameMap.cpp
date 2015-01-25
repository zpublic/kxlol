#include "MagiciteGameMap.h"

USING_NS_CC;

MagiciteGameMap::MagiciteGameMap()
{

}


MagiciteGameMap::~MagiciteGameMap()
{

}
void MagiciteGameMap::MoveMap(int seed)
{
	if (_BackGround->getPositionX() + _BackGround->getContentSize().width >= visibleSize.width)
	{
		_BackGround->setPositionX(_BackGround->getPositionX() - seed);

	}
}
bool MagiciteGameMap::init()
{
	if (!Layer::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();

	_BackGround = cocos2d::Sprite::create("ground.png");
	_BackGround->setAnchorPoint(Point::ZERO);

	this->addChild(_BackGround);
	return true;
}