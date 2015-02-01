#include "MagiciteGameWin.h"

USING_NS_CC;

MagiciteGameWin::MagiciteGameWin()
{
}


MagiciteGameWin::~MagiciteGameWin()
{
}

bool MagiciteGameWin::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    auto nextItem = MenuItemFont::create("next", [&](Ref*){});
    nextItem->setPosition(visibleSize.width / 2, visibleSize.height - nextItem->getContentSize().height * 2);

    auto mainItem = MenuItemFont::create("back to main", [&](Ref*){
        Director::getInstance()->popScene();
        Director::getInstance()->replaceScene(WelcomeScene::createScene());
    });
    mainItem->setPosition(visibleSize.width / 2, visibleSize.height - mainItem->getContentSize().height * 3);

    auto menu = Menu::create(nextItem, mainItem, nullptr);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1000);

    return true;
}

Scene* MagiciteGameWin::createScene(RenderTexture *tex)
{
    auto scene = Scene::create();
    auto layer = MagiciteGameWin::create();
    scene->addChild(layer);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto background = Sprite::createWithTexture(tex->getSprite()->getTexture());
    background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    background->setFlippedY(true);
    background->setColor(Color3B::GRAY);
    scene->addChild(background);

    return scene;
}

void MagiciteGameWin::Win(Layer* ptr)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);

    renderTexture->begin();
    ptr->getParent()->visit();
    renderTexture->end();

    Director::getInstance()->pushScene(createScene(renderTexture));
}