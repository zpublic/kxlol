#include "MainBgLayer.h"

USING_NS_CC;

bool MainBgLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

//     auto sprite = Sprite::create("HelloWorld.png");
//     sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//     this->addChild(sprite, 0);

    return true;
}
