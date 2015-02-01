#include "MagiciteGameOver.h"

USING_NS_CC;

MagiciteGameOver::MagiciteGameOver()
{

}


MagiciteGameOver::~MagiciteGameOver()
{

}

bool MagiciteGameOver::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    auto resetItem = MenuItemFont::create("reset", [&](Ref*){
        Director::getInstance()->popScene();
        Director::getInstance()->replaceScene(MagiciteScene::create());
    });
    resetItem->setPosition(visibleSize.width / 2, visibleSize.height - resetItem->getContentSize().height * 2);

    auto mainItem = MenuItemFont::create("back to main", [&](Ref*){
        Director::getInstance()->popScene();
        Director::getInstance()->replaceScene(WelcomeScene::createScene());
    });
    mainItem->setPosition(visibleSize.width / 2, visibleSize.height - mainItem->getContentSize().height * 3);

    auto menu = Menu::create(resetItem, mainItem, nullptr);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1000);

    return true;
}

Scene* MagiciteGameOver::createScene(RenderTexture *tex)
{
    auto scene = Scene::create();
    auto layer = MagiciteGameOver::create();
    scene->addChild(layer);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto background = Sprite::createWithTexture(tex->getSprite()->getTexture());

    background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    background->setFlippedY(true);
    background->setColor(Color3B::GRAY);
    scene->addChild(background);

    return scene;
}

void MagiciteGameOver::Over(Layer* ptr)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);

    renderTexture->begin();
    ptr->getParent()->visit();
    renderTexture->end();

    Director::getInstance()->pushScene(createScene(renderTexture));
}