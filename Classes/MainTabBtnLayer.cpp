#include "MainTabBtnLayer.h"
#include "MainScene.h"
#include "MainOperatePanel.h"
#include "MainOperateInfoPanel.h"

USING_NS_CC;

bool MainTabBtnLayer::init()
{
	pCurSelBtn = nullptr;
	pOpre = nullptr;
	pOpreInfo = nullptr;

    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto closeItem = MenuItemImage::create(
        "CloseSelected.png",
        "CloseSelected.png",
		CC_CALLBACK_1(MainTabBtnLayer::MainGodSpaceCallBack, this));
    closeItem->setPosition(
        Vec2(
        origin.x + 100,
        origin.y + visibleSize.height - 100
        ));
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
	pCurSelBtn = closeItem;

    closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
		CC_CALLBACK_1(MainTabBtnLayer::PlanesMgrCenter, this));
    closeItem->setPosition(
        Vec2(
        origin.x + 300,
        origin.y + visibleSize.height - 100
        ));
    menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
		CC_CALLBACK_1(MainTabBtnLayer::OriginUniverse, this));
    closeItem->setPosition(
        Vec2(
        origin.x + 500,
        origin.y + visibleSize.height - 100
        ));
    menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
		CC_CALLBACK_1(MainTabBtnLayer::PowerCapsule, this));
    closeItem->setPosition(
        Vec2(
        origin.x + 700,
        origin.y + visibleSize.height - 100
        ));
    menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    return true;
}

void MainTabBtnLayer::TabChange(Ref* pSender)
{
	if(nullptr != pCurSelBtn)
	{
		auto pCurBtn = dynamic_cast<MenuItemImage*>(pCurSelBtn);
		if(nullptr != pCurBtn)
			pCurBtn->setNormalImage(Sprite::create("CloseNormal.png"));
	}
	pCurSelBtn = pSender;
	auto pSenderBtn = dynamic_cast<MenuItemImage*>(pSender);
	if(nullptr != pSenderBtn)
		pSenderBtn->setNormalImage(Sprite::create("CloseSelected.png"));

	pOpre->removeAllChildren();
	pOpreInfo->removeAllChildren();

}

void MainTabBtnLayer::MainGodSpaceCallBack(Ref* pSender)
{
	TabChange(pSender);
	pOpre->addChild(MainOperatePanel::create());
    pOpreInfo->addChild(MainOperateInfoPanel::create());
}

void MainTabBtnLayer::PlanesMgrCenter(Ref* pSender)
{
	TabChange(pSender);
}

void MainTabBtnLayer::OriginUniverse(Ref* pSender)
{
	TabChange(pSender);
}

void MainTabBtnLayer::PowerCapsule(Ref* pSender)
{
	TabChange(pSender);
}

void MainTabBtnLayer::setOperatorLayer(Node* pOpre, Node* pOpreInfo)
{
	this->pOpre = pOpre;
	this->pOpreInfo = pOpreInfo;
	pOpre->addChild(MainOperatePanel::create());
    pOpreInfo->addChild(MainOperateInfoPanel::create());
}