#include "MagiciteScene.h"
#include "MagiciteGameLayer.h"

USING_NS_CC;

bool MagiciteScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    this->addChild(LayerColor::create(Color4B(128,128,128,255)), 0);
    this->addChild(MagiciteGameLayer::create(), 100);

    return true;
}
