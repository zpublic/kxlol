#include "MagiciteScene.h"
#include "MagiciteGameLayer.h"

USING_NS_CC;

bool MagiciteScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    this->addChild(MagiciteGameLayer::create());

    return true;
}
