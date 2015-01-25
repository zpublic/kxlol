#include "MainOperateInfoPanel.h"

USING_NS_CC;

bool MainOperateInfoPanel::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto sprBg = Sprite::create("img/MainScene/text3.png");
    sprBg->setPosition(
        Vec2(
        origin.x + visibleSize.width - 290,
        origin.y + 280
        ));
    this->addChild(sprBg, 1);

    return true;
}
