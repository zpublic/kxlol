#include "MagiciteLifeBar.h"

USING_NS_CC;

MagiciteLifeBar::MagiciteLifeBar()
{

}

MagiciteLifeBar::~MagiciteLifeBar()
{

}

bool MagiciteLifeBar::init(int max_life, const Size& size)
{
    if (!Node::init())
    {
        return false;
    }

    _max_life = _life = max_life;

    auto black = Sprite::create("img\\Magicite\\life_bar\\life_black.png");
    black->setAnchorPoint(Point::ZERO);
    black->setPosition(Vec2(0, size.height + 5));
    this->addChild(black);
    _red = Sprite::create("img\\Magicite\\life_bar\\life_red.png");
    _red->setAnchorPoint(Point::ZERO);
    _red->setPosition(Vec2(0, size.height + 5));
    this->addChild(_red);

    _seed = size.width / black->getContentSize().width;
    black->setScaleX(_seed);
    _red->setScaleX(_seed);

    return true;
}

MagiciteLifeBar* MagiciteLifeBar::create(int max_life, const Size& size)
{
    auto ptr = new MagiciteLifeBar();
    if (ptr && ptr->init(max_life, size))
    {
        return ptr;
    }
    else
    {
        CC_SAFE_DELETE(ptr);
        return nullptr;
    }
}

void MagiciteLifeBar::attact(int damage /*= 1*/)
{
    _life -= damage;
    _red->setScaleX(_seed * _life / _max_life);
}