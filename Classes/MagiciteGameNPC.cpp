#include "MagiciteGameNPC.h"
#include "MagiciteLifeBar.h"
#include "MagiciteDialogue.h"
#include <ui/CocosGUI.h>

MagiciteGameNPC::MagiciteGameNPC()
    :MagiciteGameMoveAbleLiving(Human_Type)
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
