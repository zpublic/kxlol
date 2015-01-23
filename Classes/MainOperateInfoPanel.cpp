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

    auto label = Label::createWithTTF("info", "fonts/Marker Felt.ttf", 24);
    label->setPosition(
        Vec2(
        origin.x + visibleSize.width - 50,
        origin.y + visibleSize.height - 300
        ));
    this->addChild(label, 1);

    return true;
}
