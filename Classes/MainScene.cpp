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
	auto pOpre = Node::create();
	auto pOpreInfo = Node::create();
	this->addChild(MainTabBtnLayer::create(pOpre, pOpreInfo), 2);
	this->addChild(pOpre, 3);
	this->addChild(pOpreInfo, 3);

    return true;
}
