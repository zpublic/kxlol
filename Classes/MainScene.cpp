#include "MainScene.h"
#include "MainBgLayer.h"
#include "MainBasicInfoLayer.h"
#include "MainTabBtnLayer.h"
#include "MainOperatePanel.h"
#include "MainOperateInfoPanel.h"

USING_NS_CC;

bool MainSecne::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    this->addChild(MainBgLayer::create(), 0);
    this->addChild(MainBasicInfoLayer::create(), 1);
    this->addChild(MainTabBtnLayer::create(), 2);
    this->addChild(MainOperatePanel::create(), 3);
    this->addChild(MainOperateInfoPanel::create(), 3);

    return true;
}
