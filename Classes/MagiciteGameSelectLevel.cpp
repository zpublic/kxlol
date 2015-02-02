#include "MagiciteGameSelectLevel.h"

USING_NS_CC;
USING_NS_CC_EXT;

MagiciteGameSelectLevel::MagiciteGameSelectLevel()
{

}


MagiciteGameSelectLevel::~MagiciteGameSelectLevel()
{

}

Scene* MagiciteGameSelectLevel::createScene()
{
    auto scene = Scene::create();
    auto layer = MagiciteGameSelectLevel::create();
    scene->addChild(layer);
    return scene;
}

bool MagiciteGameSelectLevel::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    initTouchDispath();

    _scroll = ScrollView::create(visibleSize, this->getContainerLayer());
    _scroll->setPosition(Point::ZERO);
    _scroll->setContentOffset(Point::ZERO);
    _scroll->setTouchEnabled(false);
    this->addChild(_scroll);
    _curPage = 0;

    return true;
}

Layer* MagiciteGameSelectLevel::getContainerLayer()
{
    auto layer = Layer::create();
    auto menu = Menu::create();
    auto size = Director::getInstance()->getVisibleSize();

    for (int i = 0; i < itemNum; ++i)
    {
        MenuItemImage* item = MenuItemImage::create(
            "CloseNormal.png", 
            "CloseSelected.png",
            [i](Ref*){Director::getInstance()->replaceScene(MagiciteScene::create());});
        item->setPosition(Vec2(((size.width / pageItem) * i + size.width / pageItem / 2), size.height / 2));
        menu->addChild(item);
    
        char str[30];
        std::sprintf(str, "%d", i);
        Label* label = Label::createWithSystemFont(str, "Arial", item->getContentSize().width / 2);
        label->setPosition(item->getContentSize().width / 2, item->getContentSize().height / 2);
        item->addChild(label);
    }

    menu->setPosition(Point::ZERO);
    layer->addChild(menu);
    return layer;
}

void MagiciteGameSelectLevel::initTouchDispath()
{
    auto listener = EventListenerTouchOneByOne::create();

    listener->onTouchBegan = [&](Touch *touch, Event *event){
        Size size = Director::getInstance()->getVisibleSize();
        _beginPoint = Director::getInstance()->convertToGL(touch->getLocation());
        _offset = _scroll->getContentOffset();

        return true;
    };

    listener->onTouchMoved = [&](Touch* touch, Event *event)
    {
        Size size = Director::getInstance()->getVisibleSize();
        Point movePoint = Director::getInstance()->convertToGL(touch->getLocation());
        Point offset = Vec2(movePoint.x - _beginPoint.x, 0);
        if ((offset.x < 0 && _curPage + 1 == pageNum) || (offset.x > 0 && _curPage == 0))
            return;

        _scroll->setContentOffset(Vec2(offset.x + _offset.x, 0));
    };

    listener->onTouchEnded = [&](Touch *touch, Event *event)
    {
        Size size = Director::getInstance()->getVisibleSize();
        Point endPoint = Director::getInstance()->convertToGL(touch->getLocation());
        int dist = endPoint.x - _beginPoint.x;

        if (abs(dist) > size.width / pageItem)
        {
            movePage(dist);
        }
        else
        {
            _scroll->setContentOffsetInDuration(Vec2(_curPage * -size.width, 0), 0.3f);
        }
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void MagiciteGameSelectLevel::movePage(int distance)
{
    Size size = Director::getInstance()->getVisibleSize();
    int seed = distance < 0 ? 1 : -1;

    if (_curPage + seed >= 0 && _curPage + seed < pageNum)
    {
        _curPage = _curPage +  (distance < 0 ? 1 :-1);
        _scroll->setContentOffsetInDuration(Vec2(_curPage * -size.width, 0), 0.5f);
    }
}