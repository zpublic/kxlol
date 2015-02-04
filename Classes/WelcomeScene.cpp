#include "WelcomeScene.h"
#include "MainScene.h"
#include "MagiciteScene.h"
#include "AequitasScene.h"
#include "MagiciteBeginMenu.h"

USING_NS_CC;

Scene* WelcomeScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = WelcomeScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool WelcomeScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    /*
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(WelcomeScene::menuEntryCallback, this));
    closeItem->setPosition(
        Vec2(
        origin.x + visibleSize.width - closeItem->getContentSize().width/2 - 200,
        origin.y + closeItem->getContentSize().height/2
        ));
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(WelcomeScene::menuEntryCallback2, this));
    closeItem->setPosition(
        Vec2(
        origin.x + visibleSize.width - closeItem->getContentSize().width/2 -100,
        origin.y + closeItem->getContentSize().height/2
        ));
    menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(WelcomeScene::menuEntryCallback3, this));
    closeItem->setPosition(
        Vec2(
        origin.x + visibleSize.width - closeItem->getContentSize().width/2,
        origin.y + closeItem->getContentSize().height/2
        ));
    menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    
    auto label = Label::createWithTTF("Welcome", "fonts/Marker Felt.ttf", 24);
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);*/
    
    return true;
}

void WelcomeScene::onEnter()
{
    Director::getInstance()->replaceScene(MagiciteBeginMenu::createScene());
}

void WelcomeScene::menuEntryCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(MainSecne::create());
}

void WelcomeScene::menuEntryCallback2(Ref* pSender)
{
    Director::getInstance()->replaceScene(MagiciteGameSelectLevel::create());
}

void WelcomeScene::menuEntryCallback3(Ref* pSender)
{
    Director::getInstance()->replaceScene(AequitasScene::create());
}

