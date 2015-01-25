#include "MainBasicInfoLayer.h"

USING_NS_CC;

bool MainBasicInfoLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /// "主神：老肉鸡"
	auto sprName = Sprite::create("img/avatar/1.png");
	sprName->setPosition(
		Vec2(
			origin.x + 450,
			origin.y + visibleSize.height - 60));
	this->addChild(sprName);
	auto sprNameBg = Sprite::create("img/MainScene/text1.png");
	sprNameBg->setPosition(
		Vec2(
			origin.x + 490,
			origin.y + visibleSize.height - 60));
	sprNameBg->setAnchorPoint(Vec2(0, 0.5));
	this->addChild(sprNameBg);
    auto label = Label::createWithTTF("zapline", "fonts/Marker Felt.ttf", 24);
    label->setPosition(
        Vec2(
        origin.x + 500,
        origin.y + visibleSize.height - 60));
	label->setAnchorPoint(Vec2(0, 0.5));
    this->addChild(label, 1);

    /// 空虚神力：1024
    auto sprGodPower = Sprite::create("img/MainScene/godpower.png");
	sprGodPower->setPosition(
		Vec2(
			origin.x + 720,
			origin.y + visibleSize.height - 60));
	this->addChild(sprGodPower);
	auto sprGodPowerBg = Sprite::create("img/MainScene/text1.png");
	sprGodPowerBg->setPosition(
		Vec2(
			origin.x + 760,
			origin.y + visibleSize.height - 60));
	sprGodPowerBg->setAnchorPoint(Vec2(0, 0.5));
	this->addChild(sprGodPowerBg);
    auto lblGodPower = Label::createWithTTF("1024", "fonts/Marker Felt.ttf", 24);
    lblGodPower->setPosition(
        Vec2(
        origin.x + 770,
        origin.y + visibleSize.height - 60));
	lblGodPower->setAnchorPoint(Vec2(0, 0.5));
    this->addChild(lblGodPower, 1);

    return true;
}
