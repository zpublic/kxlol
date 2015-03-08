#include "MagiciteGameNPC.h"
#include "MagiciteLifeBar.h"
#include "MagiciteDialogue.h"
#include <ui/CocosGUI.h>

MagiciteGameNPC::MagiciteGameNPC()
    :MagiciteGameMoveAbleLiving(Human_Type)
    , _lblName(nullptr)
{
    this->_health_point = 1;
    this->_mana_point = 1;
}

void MagiciteGameNPC::initAnimation()
{

}


bool MagiciteGameNPC::init()
{
    if(!MagiciteGameMoveAbleLiving::initWithFile("img\\Magicite\\player\\player_stop.png"))
        return false;
    _life_bar->setVisible(false);
    auto btnNPC = cocos2d::ui::Button::create("img/_blank.png");
    this->getContentSize();
    btnNPC->setZoomScale(1.0f);
    btnNPC->setScale(this->getContentSize().width / btnNPC->getContentSize().width,
       this->getContentSize().height / btnNPC->getContentSize().height);
    btnNPC->setAnchorPoint(cocos2d::Vec2(0.0f, 0.0f));
    this->addChild(btnNPC);
    btnNPC->addClickEventListener([](Ref*){
        cocos2d::Director::getInstance()->getRunningScene()->addChild(MagiciteDialogue::create(1));
    });

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
    const char* const fontName = "Microsoft YaHei";
#endif

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    const char* const fontName = "Droid Sans Fallback";
#endif

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    const char* const fontName = "Heiti SC";
#endif

//若您的目标系统不是以上的几种系统，请按照以上格式在下面添加您的目标系统和对应的默认字体名称

//------------------------------------------------------------------------------------------
    _lblName = cocos2d::Label::create("", fontName, 16);
    this->addChild(_lblName);
    _lblName->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
    _lblName->setPosition(this->getContentSize().width / 2, this->getContentSize().height + 10.0f);

    return true;
}

cocos2d::RepeatForever* MagiciteGameNPC::createAnimateJump()
{
    return cocos2d::RepeatForever::create(cocos2d::DelayTime::create(1.0f));
}

cocos2d::RepeatForever* MagiciteGameNPC::createAnimateMove()
{
    return cocos2d::RepeatForever::create(cocos2d::DelayTime::create(1.0f));
}

void MagiciteGameNPC::setNpcName( const std::string& strName )
{
    _lblName->setString(strName);
}
