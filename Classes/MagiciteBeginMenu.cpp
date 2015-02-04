#include "MagiciteBeginMenu.h"
#include "MagiciteScene.h"
#include "MagiciteGameSelectLevel.h"


bool MagiciteBeginMenu::init()
{
    if(!Layer::init())
        return false;

    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    auto bmFont =  cocos2d::Label::createWithBMFont("fonts/BeginMenu.fnt", "Begin!", cocos2d::TextHAlignment::RIGHT);
    auto menuItem = cocos2d::MenuItemLabel::create(bmFont, [&](Ref*){
        cocos2d::Director::getInstance()->replaceScene(MagiciteScene::create());
    });
    menuItem->setAnchorPoint(cocos2d::Vec2(1, 0.5));
    menuItem->setPosition(origin.x + visibleSize.width - 40, origin.y + 150);
    auto menu = cocos2d::Menu::create(menuItem, nullptr);
    menu->setPosition(cocos2d::Point::ZERO);
    this->addChild(menu);

    bmFont =  cocos2d::Label::createWithBMFont("fonts/BeginMenu.fnt", "Select Pass", cocos2d::TextHAlignment::RIGHT);
    menuItem = cocos2d::MenuItemLabel::create(bmFont, [&](Ref*){
        cocos2d::Director::getInstance()->replaceScene(MagiciteGameSelectLevel::create());
    });
    menuItem->setAnchorPoint(cocos2d::Vec2(1, 0.5));
    menuItem->setPosition(origin.x + visibleSize.width - 40, origin.y + 100);
    menu = cocos2d::Menu::create(menuItem, nullptr);
    menu->setPosition(cocos2d::Point::ZERO);
    this->addChild(menu);

    bmFont =  cocos2d::Label::createWithBMFont("fonts/BeginMenu.fnt", "Quit Game", cocos2d::TextHAlignment::RIGHT);
    menuItem = cocos2d::MenuItemLabel::create(bmFont, [&](Ref*){
        cocos2d::Director::getInstance()->end();
    });
    menuItem->setAnchorPoint(cocos2d::Vec2(1, 0.5));
    menuItem->setPosition(origin.x + visibleSize.width - 40, origin.y + 50);
    menu = cocos2d::Menu::create(menuItem, nullptr);
    menu->setPosition(cocos2d::Point::ZERO);
    this->addChild(menu);

    auto logo = cocos2d::Label::createWithBMFont("fonts/BeginMenu.fnt", "KXLOL", cocos2d::TextHAlignment::CENTER);
    logo->setScale(3.0f);
    logo->setAnchorPoint(cocos2d::Vec2(0.5, 1));
    logo->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 40);
    this->addChild(logo);
    cocos2d::Vector<cocos2d::FiniteTimeAction*> actions;
    actions.pushBack(cocos2d::ScaleTo::create(0.2, 3.5));
    actions.pushBack(cocos2d::ScaleTo::create(0.1, 3.0));
    actions.pushBack(cocos2d::ScaleTo::create(0.2, 3.5));
    actions.pushBack(cocos2d::ScaleTo::create(0.1, 3.0));
    actions.pushBack(cocos2d::DelayTime::create(0.5));
    logo->runAction(cocos2d::RepeatForever::create(cocos2d::Sequence::create(actions)));

    return true;
}

cocos2d::Scene* MagiciteBeginMenu::createScene()
{
    auto scene = cocos2d::Scene::create();
    auto layer = MagiciteBeginMenu::create();
    scene->addChild(layer);
    layer->setAnchorPoint(cocos2d::Vec2(0, 0));

    return scene;
}