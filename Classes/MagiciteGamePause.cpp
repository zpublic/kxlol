#include "MagiciteGamePause.h"

USING_NS_CC;

MagiciteGamePause::MagiciteGamePause()
{

}


MagiciteGamePause::~MagiciteGamePause()
{

}

bool MagiciteGamePause::init()
{
    if (!Scene::init())
    {
        return false;
    }
    auto layer = Layer::create();
    this->addChild(layer);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    auto continueItem = MenuItemFont::create("continue", [&](Ref*){
        Director::getInstance()->popScene();
    });
    continueItem->setPosition(visibleSize.width / 2, visibleSize.height  - continueItem->getContentSize().height);

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

    auto menu = Menu::create(continueItem, resetItem, mainItem, nullptr);
    menu->setPosition(Point::ZERO);
    layer->addChild(menu, 1000);

    return true;
}

MagiciteGamePause* MagiciteGamePause::create(RenderTexture *tex)
{
    auto scene = new MagiciteGamePause();
    if (scene && scene->init())
    {
        scene->autorelease();

        auto visibleSize = Director::getInstance()->getVisibleSize();
        auto background = Sprite::createWithTexture(tex->getSprite()->getTexture());
        background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
        background->setFlippedY(true);
        background->setColor(Color3B::GRAY);
        scene->addChild(background);
        return scene;
    }
    else
    {
        CC_SAFE_DELETE(scene);
        return nullptr;
    }
}

void MagiciteGamePause::Pause(Layer* ptr)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);

    renderTexture->begin();
    ptr->getParent()->visit();
    renderTexture->end();

    Director::getInstance()->pushScene(create(renderTexture));
}