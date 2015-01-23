#include "MainScene.h"
#include "MainBgLayer.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool MainSecne::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    this->addChild(MainBgLayer::create());

    return true;
}
