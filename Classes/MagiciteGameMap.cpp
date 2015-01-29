#include "MagiciteGameMap.h"

USING_NS_CC;

MagiciteGameMap::MagiciteGameMap()
{

}

MagiciteGameMap::~MagiciteGameMap()
{

}

bool MagiciteGameMap::init(TMXTiledMap* map)
{
    if (!Layer::init())
    {
        return false;
    }
    _visibleSize = Director::getInstance()->getVisibleSize();

    _BackGround = map;
    _BackGround->setAnchorPoint(Point::ZERO);
    this->addChild(_BackGround);

    return true;
}

Size MagiciteGameMap::getBackSize() const
{
    return _BackGround->getContentSize();
}

MagiciteGameMap* MagiciteGameMap::create(TMXTiledMap* map)
{
    auto ptr = new MagiciteGameMap();
    if (ptr && ptr->init(map))
    {
        ptr->autorelease();
        return ptr;
    }
    else
    {
        CC_SAFE_DELETE(ptr);
        return nullptr;
    }
}