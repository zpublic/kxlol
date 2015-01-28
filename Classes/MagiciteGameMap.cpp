#include "MagiciteGameMap.h"

USING_NS_CC;

MagiciteGameMap::MagiciteGameMap()
{

}

MagiciteGameMap::~MagiciteGameMap()
{

}

bool MagiciteGameMap::init()
{
    if (!Layer::init())
    {
        return false;
    }
    _visibleSize = Director::getInstance()->getVisibleSize();

    _BackGround = cocos2d::Sprite::create("ground.png");
    _BackGround->setAnchorPoint(Point::ZERO);
    this->addChild(_BackGround);

    return true;
}

Size MagiciteGameMap::getBackSize() const
{
    return _BackGround->getContentSize();
}
