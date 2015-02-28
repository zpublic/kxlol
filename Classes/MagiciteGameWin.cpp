#include "MagiciteGameWin.h"
#include "WelcomeScene.h"
#include "MagiciteScene.h"

USING_NS_CC;

MagiciteGameWin::MagiciteGameWin()
{
}


MagiciteGameWin::~MagiciteGameWin()
{
}

bool MagiciteGameWin::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto layer = Layer::create();
    this->addChild(layer);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    auto nextItem = MenuItemFont::create("next", [&](Ref*){
        Director::getInstance()->popScene();
        MagiciteScene::setLevel(MagiciteScene::getLevel() + 1);
        Director::getInstance()->replaceScene(MagiciteScene::create());
    });
    nextItem->setPosition(visibleSize.width / 2, visibleSize.height - nextItem->getContentSize().height * 2);

    auto mainItem = MenuItemFont::create("back to main", [&](Ref*){
        Director::getInstance()->popScene();
        Director::getInstance()->replaceScene(WelcomeScene::createScene());
    });
    mainItem->setPosition(visibleSize.width / 2, visibleSize.height - mainItem->getContentSize().height * 3);

    auto menu = Menu::create(nextItem, mainItem, nullptr);
    menu->setPosition(Point::ZERO);
    layer->addChild(menu, 1000);

    return true;
}

MagiciteGameWin* MagiciteGameWin::create(RenderTexture *tex)
{
    auto scene = new MagiciteGameWin();
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

void MagiciteGameWin::Win(Layer* ptr)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);

    renderTexture->begin();
    ptr->getParent()->visit();
    renderTexture->end();

    Director::getInstance()->pushScene(create(renderTexture));
}