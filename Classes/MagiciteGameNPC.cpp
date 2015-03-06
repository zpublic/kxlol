#include "MagiciteGameNPC.h"
#include "MagiciteLifeBar.h"

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
