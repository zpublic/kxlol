#include "MainOperatePanel.h"
#include "ui\UIButton.h"

USING_NS_CC;

bool MainOperatePanel::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto btn = ui::Button::create("img/MainScene/build.png");
	btn->addClickEventListener(CC_CALLBACK_1(MainOperatePanel::TabBtnCallback, this));
	btn->setPosition(
        Vec2(
        origin.x + 200,
        origin.y + visibleSize.height - 230
        ));
	this->addChild(btn);

	btn = ui::Button::create("img/MainScene/make.png");
	btn->addClickEventListener(CC_CALLBACK_1(MainOperatePanel::TabBtnCallback, this));
	btn->setPosition(
        Vec2(
        origin.x + 100,
        origin.y + visibleSize.height - 380
        ));
	this->addChild(btn);

	btn = ui::Button::create("img/MainScene/train.png");
	btn->addClickEventListener(CC_CALLBACK_1(MainOperatePanel::TabBtnCallback, this));
	btn->setPosition(
        Vec2(
        origin.x + 300,
        origin.y + visibleSize.height - 380
        ));
	this->addChild(btn);

	btn = ui::Button::create("img/MainScene/linkvoid.png");
	btn->addTouchEventListener(CC_CALLBACK_2(MainOperatePanel::LinkVoidCallBack, this));
	btn->setPosition(
        Vec2(
        origin.x + 200,
		80
        ));
	btn->setZoomScale(0);
	auto sprOutLine = Sprite::create("img/MainScene/linkvoid_outline.png");
	btn->addChild(sprOutLine, -1, 8);
	sprOutLine->setVisible(false);
	sprOutLine->setAnchorPoint(Vec2(0, 0));
	this->addChild(btn);

    return true;
}

void MainOperatePanel::TabBtnCallback(Ref* pSender)
{
	;
}

void MainOperatePanel::LinkVoidCallBack(Ref* pSender, ui::Widget::TouchEventType _event)
{
	Node* _outline = nullptr;
	auto temp = dynamic_cast<Node*>(pSender);
	if(nullptr != temp)
	{
		_outline = temp->getChildByTag(8);
	}
	if(_event == ui::Widget::TouchEventType::BEGAN || _event == ui::Widget::TouchEventType::MOVED)
	{
		if(nullptr != temp)_outline->setVisible(true);
	}
	else
	{
		if(nullptr != temp)_outline->setVisible(false);
	}
}