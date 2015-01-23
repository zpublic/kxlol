#include "MagiciteGameLayer.h"

USING_NS_CC;

bool MagiciteGameLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    auto act = MoveTo::create(1.0f, Vec2(250, 200));
    sprite->runAction(act);

    this->addChild(sprite, 0);

    return true;
}
