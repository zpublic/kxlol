#include "MainTabBtnLayer.h"

USING_NS_CC;

bool MainTabBtnLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(MainTabBtnLayer::TabBtnCallback, this));
    closeItem->setPosition(
        Vec2(
        origin.x + 100,
        origin.y + visibleSize.height - 100
        ));
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(MainTabBtnLayer::TabBtnCallback, this));
    closeItem->setPosition(
        Vec2(
        origin.x + 300,
        origin.y + visibleSize.height - 100
        ));
    menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(MainTabBtnLayer::TabBtnCallback, this));
    closeItem->setPosition(
        Vec2(
        origin.x + 500,
        origin.y + visibleSize.height - 100
        ));
    menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(MainTabBtnLayer::TabBtnCallback, this));
    closeItem->setPosition(
        Vec2(
        origin.x + 700,
        origin.y + visibleSize.height - 100
        ));
    menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    return true;
}

void MainTabBtnLayer::TabBtnCallback(Ref* pSender)
{
    ;
}
