#include "MainScene.h"
#include "MainBgLayer.h"
#include "MainBasicInfoLayer.h"
#include "MainTabBtnLayer.h"

USING_NS_CC;

bool MainSecne::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    this->addChild(MainBgLayer::create(), 0);
    this->addChild(MainBasicInfoLayer::create(), 1);
    this->addChild(MainTabBtnLayer::create(), 1);

    return true;
}
