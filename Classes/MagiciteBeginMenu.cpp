#include "MagiciteBeginMenu.h"
#include "MagiciteScene.h"
#include "MagiciteGameSelectLevel.h"
#include "AequitasScene.h"


bool MagiciteBeginMenu::init()
{
    if(!Scene::init())
        return false;

    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    auto background = cocos2d::Sprite::create("img\\Magicite\\background\\background_main.png");
    background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    this->addChild(background);

    auto ttfFont = cocos2d::Label::createWithTTF("Begin!", "fonts/Marker Felt.ttf", 32.0f, cocos2d::Size::ZERO,cocos2d::TextHAlignment::RIGHT);
    ttfFont->enableOutline(cocos2d::Color4B(0.0f, 0.0f, 0.0f, 255.0f), 2);
    auto menuItem = cocos2d::MenuItemLabel::create(ttfFont, [&](Ref*){
        cocos2d::Director::getInstance()->replaceScene(MagiciteScene::create());
    });
    menuItem->setAnchorPoint(cocos2d::Vec2(1, 0.5));
    menuItem->setPosition(origin.x + visibleSize.width - 40, origin.y + 200);
    auto menu = cocos2d::Menu::create(menuItem, nullptr);
    menu->setPosition(cocos2d::Point::ZERO);
    this->addChild(menu);

    ttfFont = cocos2d::Label::createWithTTF("Select Pass", "fonts/Marker Felt.ttf", 32.0f, cocos2d::Size::ZERO,cocos2d::TextHAlignment::RIGHT);
    ttfFont->enableOutline(cocos2d::Color4B(0.0f, 0.0f, 0.0f, 255.0f), 2);
    menuItem = cocos2d::MenuItemLabel::create(ttfFont, [&](Ref*){
        cocos2d::Director::getInstance()->replaceScene(MagiciteGameSelectLevel::create());
    });
    menuItem->setAnchorPoint(cocos2d::Vec2(1, 0.5));
    menuItem->setPosition(origin.x + visibleSize.width - 40, origin.y + 150);
    menu = cocos2d::Menu::create(menuItem, nullptr);
    menu->setPosition(cocos2d::Point::ZERO);
    this->addChild(menu);

    ttfFont = cocos2d::Label::createWithTTF("Piano", "fonts/Marker Felt.ttf", 32.0f, cocos2d::Size::ZERO,cocos2d::TextHAlignment::RIGHT);
    ttfFont->enableOutline(cocos2d::Color4B(0.0f, 0.0f, 0.0f, 255.0f), 2);
    menuItem = cocos2d::MenuItemLabel::create(ttfFont, [&](Ref*){
       cocos2d::Director::getInstance()->replaceScene(AequitasScene::create());
    });
    menuItem->setAnchorPoint(cocos2d::Vec2(1, 0.5));
    menuItem->setPosition(origin.x + visibleSize.width - 40, origin.y + 100);
    menu = cocos2d::Menu::create(menuItem, nullptr);
    menu->setPosition(cocos2d::Point::ZERO);
    this->addChild(menu);

    ttfFont = cocos2d::Label::createWithTTF("Quit Game", "fonts/Marker Felt.ttf", 32.0f, cocos2d::Size::ZERO,cocos2d::TextHAlignment::RIGHT);
    ttfFont->enableOutline(cocos2d::Color4B(0.0f, 0.0f, 0.0f, 255.0f), 2);
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

