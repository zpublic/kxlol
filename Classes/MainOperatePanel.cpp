#include "MainOperatePanel.h"

USING_NS_CC;

bool MainOperatePanel::init()
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
        CC_CALLBACK_1(MainOperatePanel::TabBtnCallback, this));
    closeItem->setPosition(
        Vec2(
        origin.x + 400,
        origin.y + visibleSize.height - 300
        ));
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(MainOperatePanel::TabBtnCallback, this));
    closeItem->setPosition(
        Vec2(
        origin.x + 200,
        origin.y + visibleSize.height - 500
        ));
    menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(MainOperatePanel::TabBtnCallback, this));
    closeItem->setPosition(
        Vec2(
        origin.x + 400,
        origin.y + visibleSize.height - 500
        ));
    menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(MainOperatePanel::TabBtnCallback, this));
    closeItem->setPosition(
        Vec2(
        origin.x + 600,
        origin.y + visibleSize.height - 500
        ));
    menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    return true;
}

void MainOperatePanel::TabBtnCallback(Ref* pSender)
{
    ;
}
