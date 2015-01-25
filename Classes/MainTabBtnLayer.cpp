#include "MainTabBtnLayer.h"
#include "MainScene.h"
#include "MainOperatePanel.h"
#include "MainOperateInfoPanel.h"
#include "ui\UICheckBox.h"

#define CHECK_BCURBTN(_sel, _cur) if(_sel == _cur){\
	auto temp = dynamic_cast<cocos2d::ui::CheckBox*>(_cur);\
	if(nullptr != temp)temp->setSelected(true);\
	return;}

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

	auto check = cocos2d::ui::CheckBox::create();
	check->loadTextureBackGround("img/MainScene/maingodspace.png");
	check->loadTextureBackGroundSelected("img/MainScene/maingodspace.png");
	check->loadTextureFrontCross("img/MainScene/maingodspace_sel.png");
	check->addClickEventListener(CC_CALLBACK_1(MainTabBtnLayer::MainGodSpaceCallBack, this));
	this->addChild(check);
	check->setPosition(
        Vec2(
        origin.x + 115,
        origin.y + visibleSize.height - 50
		));
	check->setSelected(true);
	pCurSelBtn = check;

	check = cocos2d::ui::CheckBox::create();
	check->loadTextureBackGround("img/MainScene/planemgrcenter.png");
	check->loadTextureBackGroundSelected("img/MainScene/planemgrcenter.png");
	check->loadTextureFrontCross("img/MainScene/planemgrcenter_sel.png");
	check->addClickEventListener(CC_CALLBACK_1(MainTabBtnLayer::PlanesMgrCenter, this));
	this->addChild(check);
	check->setPosition(
		 Vec2(
        origin.x + 275,
        origin.y + visibleSize.height - 50
        ));

	check = cocos2d::ui::CheckBox::create();
	check->loadTextureBackGround("img/MainScene/originuniversal.png");
	check->loadTextureBackGroundSelected("img/MainScene/originuniversal.png");
	check->loadTextureFrontCross("img/MainScene/originuniversal_sel.png");
	check->addClickEventListener(CC_CALLBACK_1(MainTabBtnLayer::OriginUniverse, this));
	this->addChild(check);
	check->setPosition(
        Vec2(
        origin.x + 115,
        origin.y + visibleSize.height - 100
        ));

	check = cocos2d::ui::CheckBox::create();
	check->loadTextureBackGround("img/MainScene/powercaptule.png");
	check->loadTextureBackGroundSelected("img/MainScene/powercaptule.png");
	check->loadTextureFrontCross("img/MainScene/powercaptule_sel.png");
	check->addClickEventListener(CC_CALLBACK_1(MainTabBtnLayer::PowerCapsule, this));
	this->addChild(check);
	check->setPosition(
        Vec2(
        origin.x + 275,
        origin.y + visibleSize.height - 100
        ));

    return true;
}

void MainTabBtnLayer::TabChange(Ref* pSender)
{
	if(nullptr != pCurSelBtn)
	{
		auto pCurBtn = dynamic_cast<ui::CheckBox*>(pCurSelBtn);
		if(nullptr != pCurBtn)
			pCurBtn->setSelected(false);
	}
	pCurSelBtn = pSender;

	pOpre->removeAllChildren();
	pOpreInfo->removeAllChildren();

}

void MainTabBtnLayer::MainGodSpaceCallBack(Ref* pSender)
{
	CHECK_BCURBTN(pSender, pCurSelBtn);
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