#include "MagiciteGameMap.h"

USING_NS_CC;

MagiciteGameMap::MagiciteGameMap()
{
    _left_open = true;
    _right_open = true;
}

MagiciteGameMap::~MagiciteGameMap()
{

}

void MagiciteGameMap::MoveMap(int seed)
{
    if (seed < 0)
    {
        if (_BackGround->getPositionX() + seed <= 0)
        {
            _BackGround->setPositionX(_BackGround->getPositionX() - seed);
            if (_right_open == false)
            {
                _right_open = true;
            }
        }
        else
        {
            _left_open = false;
        }
    }
    else
    {
        if (_BackGround->getPositionX() + _BackGround->getContentSize().width >= _visibleSize.width)
        {
            _BackGround->setPositionX(_BackGround->getPositionX() - seed);
            if (_left_open == false)
            {
                _left_open = true;
            }
        }
        else
        {
            _right_open = false;
        }
    }
}

bool MagiciteGameMap::is_left_open() const
{
    return _left_open;
}

bool MagiciteGameMap::is_right_open() const
{
    return _right_open;
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