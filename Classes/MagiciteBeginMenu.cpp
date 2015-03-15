#include "MagiciteBeginMenu.h"
#include "MagiciteScene.h"
#include "MagiciteCaptionScene.h"
#include "MagiciteGameSelectLevel.h"
#include "AequitasScene.h"


bool MagiciteBeginMenu::init()
{
    if(!Scene::init())
        return false;

    srand(time(0));

    if(rand() % 2 == 1)
    {
        initBeginMenu2();
        return true;
    }

    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    auto background = cocos2d::Sprite::create("img\\Magicite\\background\\background_main.png");
    background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    this->addChild(background);

    auto ttfFont = cocos2d::Label::createWithTTF("Begin!", "fonts/Marker Felt.ttf", 32.0f, cocos2d::Size::ZERO,cocos2d::TextHAlignment::RIGHT);
    auto menuItem = cocos2d::MenuItemLabel::create(ttfFont, [&](Ref*){
        cocos2d::Director::getInstance()->replaceScene(MagiciteCaptionScene::create());
    });
    menuItem->setAnchorPoint(cocos2d::Vec2(1, 0.5));
    menuItem->setPosition(origin.x + visibleSize.width - 40, origin.y + 200);
    auto menu = cocos2d::Menu::create(menuItem, nullptr);
    menu->setPosition(cocos2d::Point::ZERO);
    this->addChild(menu);

    /*ttfFont = cocos2d::Label::createWithTTF("Select Pass", "fonts/Marker Felt.ttf", 32.0f, cocos2d::Size::ZERO,cocos2d::TextHAlignment::RIGHT);
    menuItem = cocos2d::MenuItemLabel::create(ttfFont, [&](Ref*){
    cocos2d::Director::getInstance()->replaceScene(MagiciteGameSelectLevel::create());
    });
    menuItem->setAnchorPoint(cocos2d::Vec2(1, 0.5));
    menuItem->setPosition(origin.x + visibleSize.width - 40, origin.y + 150);
    menu = cocos2d::Menu::create(menuItem, nullptr);
    menu->setPosition(cocos2d::Point::ZERO);
    this->addChild(menu);*/

    ttfFont = cocos2d::Label::createWithTTF("Piano", "fonts/Marker Felt.ttf", 32.0f, cocos2d::Size::ZERO,cocos2d::TextHAlignment::RIGHT);
    menuItem = cocos2d::MenuItemLabel::create(ttfFont, [&](Ref*){
       cocos2d::Director::getInstance()->replaceScene(AequitasScene::create());
    });
    menuItem->setAnchorPoint(cocos2d::Vec2(1, 0.5));
    menuItem->setPosition(origin.x + visibleSize.width - 40, origin.y + 100);
    menu = cocos2d::Menu::create(menuItem, nullptr);
    menu->setPosition(cocos2d::Point::ZERO);
    this->addChild(menu);

    ttfFont = cocos2d::Label::createWithTTF("Quit Game", "fonts/Marker Felt.ttf", 32.0f, cocos2d::Size::ZERO,cocos2d::TextHAlignment::RIGHT);
    menuItem = cocos2d::MenuItemLabel::create(ttfFont, [&](Ref*){
        cocos2d::Director::getInstance()->end();
    });
    menuItem->setAnchorPoint(cocos2d::Vec2(1, 0.5));
    menuItem->setPosition(origin.x + visibleSize.width - 40, origin.y + 50);
    menu = cocos2d::Menu::create(menuItem, nullptr);
    menu->setPosition(cocos2d::Point::ZERO);
    this->addChild(menu);

    auto logo = cocos2d::Label::createWithTTF("KXLOL", "fonts/Marker Felt.ttf", 72.0f, cocos2d::Size::ZERO, cocos2d::TextHAlignment::CENTER);
    logo->enableOutline(cocos2d::Color4B(0.0f, 0.0f, 0.0f, 255.0f), 4);
    logo->setAnchorPoint(cocos2d::Vec2(0.5, 1));
    logo->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 100);
    this->addChild(logo);
    cocos2d::Vector<cocos2d::FiniteTimeAction*> actions;
    actions.pushBack(cocos2d::ScaleTo::create(0.2f, 1.2f));
    actions.pushBack(cocos2d::ScaleTo::create(0.1f, 1.0f));
    actions.pushBack(cocos2d::ScaleTo::create(0.2f, 1.2f));
    actions.pushBack(cocos2d::ScaleTo::create(0.1f, 1.0f));
    actions.pushBack(cocos2d::DelayTime::create(0.5f));
    logo->runAction(cocos2d::RepeatForever::create(cocos2d::Sequence::create(actions)));

    return true;
}

void MagiciteBeginMenu::initBeginMenu2()
{
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    auto background = cocos2d::Sprite::create("img/Magicite/background/background_menu.png");
    background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    this->addChild(background);

    cocos2d::Vector<cocos2d::Menu*> menus;

    auto spr = cocos2d::Sprite::create("img/Magicite/UI/menu.png", cocos2d::Rect(0.0f, 0.0f, 154.0f, 65.0f));
    auto menuItem = cocos2d::MenuItemSprite::create(spr, spr);
    menuItem->setCallback([](cocos2d::Ref* ){
        cocos2d::Director::getInstance()->replaceScene(MagiciteCaptionScene::create());
    });
    menuItem->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    auto menu = cocos2d::Menu::create(menuItem, nullptr);
    menu->setPosition(0.0f, 0.0f);
    this->addChild(menu);
    menus.pushBack(menu);

    spr = cocos2d::Sprite::create("img/Magicite/UI/menu.png", cocos2d::Rect(0.0f, 65.0f, 154.0f, 65.0f));
    menuItem = cocos2d::MenuItemSprite::create(spr, spr);
    menuItem->setCallback([](cocos2d::Ref* ){
        cocos2d::Director::getInstance()->end();
    });
    menuItem->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 65.0f);
    menu = cocos2d::Menu::create(menuItem, nullptr);
    menu->setPosition(0.0f, 0.0f);
    this->addChild(menu);
    menus.pushBack(menu);

}

