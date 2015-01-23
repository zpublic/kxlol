#include "MainBasicInfoLayer.h"

USING_NS_CC;

bool MainBasicInfoLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /// "主神：老肉鸡"
    auto label = Label::createWithTTF("name : zapline", "fonts/Marker Felt.ttf", 24);
    label->setPosition(
        Vec2(
        origin.x + 500,
        origin.y + visibleSize.height - 50));
    this->addChild(label, 1);

    /// 空虚神力：1024
    auto label2 = Label::createWithTTF("kx : 1024", "fonts/Marker Felt.ttf", 24);
    label2->setPosition(
        Vec2(
        origin.x + 750,
        origin.y + visibleSize.height - 50));
    this->addChild(label2, 1);

    return true;
}
