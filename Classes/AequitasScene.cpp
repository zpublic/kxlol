#include "AequitasScene.h"
#include "AequitasLayer.h"

USING_NS_CC;

bool AequitasScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    this->addChild(LayerColor::create(Color4B(128,128,128,255)), 0);
    this->addChild(AequitasLayer::create(), 100);

    return true;
}
